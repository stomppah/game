#include "window.h"

#include <cstdint>
#include <optional>
#include <print>
#include <queue>
#include <ranges>

#include "opengl.h"

#include "auto_release.h"
#include "error.h"
#include "event.h"
#include "log.h"
#include "stop_event.h"

#pragma comment(lib, "OpenGL32.lib")

namespace
{
    PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB{};
    PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB{};

    auto g_event_queue = std::queue<game::Event>{};

    auto APIENTRY opengl_debug_callback(
        ::GLenum source,
        ::GLenum type,
        ::GLuint id,
        ::GLenum severity,
        ::GLsizei length,
        const GLchar *message,
        [[maybe_unused]] const void *userParam) -> void
    {
        std::print("{} {} {} {} {} {}", source, type, id, severity, length, message);
    }

    auto CALLBACK window_proc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) -> LRESULT
    {
        switch (Msg)
        {
        case WM_CLOSE:
            g_event_queue.emplace(game::StopEvent{});
            break;
        case WM_KEYDOWN:
            /***
                [DEBUG] key down 87 = W
                [DEBUG] key down 83 = S
                [DEBUG] key down 65 = A
                [DEBUG] key down 68 = D
                [DEBUG] key down 38 = Up
                [DEBUG] key down 40 = Down
                [DEBUG] key down 37 = Left
                [DEBUG] key down 39 = Right
                [DEBUG] key down 27 = Esc
             */
            game::log::debug("key down {}", wParam);
            break;

        default:
            break;
        };

        return ::DefWindowProcA(hWnd, Msg, wParam, lParam);
    }

    template <class T>
    auto resolve_gl_function(T &function, const std::string &name) -> void
    {
        const auto address = ::wglGetProcAddress(name.c_str());
        game::ensure(address, "could not resolve {}", name);

        function = reinterpret_cast<T>(address);
    }

    auto init_opengl(HDC dc) -> void
    {
        int pixel_format_attribs[] = {
            WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
            WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
            WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
            WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
            WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
            WGL_COLOR_BITS_ARB, 32,
            WGL_DEPTH_BITS_ARB, 24,
            WGL_STENCIL_BITS_ARB, 8, 0

        };

        auto pixel_format = 0;
        auto num_formats = UINT{};
        ::wglChoosePixelFormatARB(dc, pixel_format_attribs, 0, 1, &pixel_format, &num_formats);
        game::ensure(num_formats != 0u, "could not choose a pixel format");

        auto pfd = ::PIXELFORMATDESCRIPTOR{};
        game::ensure(::DescribePixelFormat(dc, pixel_format, sizeof(pfd), &pfd) != 0, "could not describe pixel format");
        game::ensure(::SetPixelFormat(dc, pixel_format, &pfd) == TRUE, "could not set pixel format");

        int gl_attribs[] = {
            WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
            WGL_CONTEXT_MINOR_VERSION_ARB, 6,
            WGL_CONTEXT_PROFILE_MASK_ARB,
            WGL_CONTEXT_CORE_PROFILE_BIT_ARB, 0};

        auto context = ::wglCreateContextAttribsARB(dc, 0, gl_attribs);
        game::ensure(context != nullptr, "failed to create wgl context");

        game::ensure(::wglMakeCurrent(dc, context) == TRUE, "failed to make context current");
    }

    auto resolve_wgl_functions(HINSTANCE instance) -> void
    {
        auto wc = ::WNDCLASS{};
        wc.lpfnWndProc = ::DefWindowProc;
        wc.lpszClassName = "dummy window";
        wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        wc.hInstance = instance;

        game::ensure(::RegisterClassA(&wc) != 0, "could not register dummy window");

        auto dummy_window = game::AutoRelease<::HWND>{
            ::CreateWindowExA(
                0,                // style
                wc.lpszClassName, // classname
                wc.lpszClassName,
                0,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT, 0, 0, wc.hInstance, 0),
            ::DestroyWindow};

        game::ensure(dummy_window, "could not create dummy window");

        auto dc = game::AutoRelease<::HDC>{
            ::GetDC(dummy_window), [&dummy_window](auto dc)
            {
                ::ReleaseDC(dummy_window, dc);
            }};

        auto pfd = ::PIXELFORMATDESCRIPTOR{};
        pfd.nSize = sizeof(::PIXELFORMATDESCRIPTOR);
        pfd.nVersion = 1;
        pfd.iPixelType = PFD_TYPE_RGBA;
        pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        pfd.cColorBits = 32;
        pfd.cAlphaBits = 8;
        pfd.iLayerType = PFD_MAIN_PLANE;
        pfd.cDepthBits = 24;
        pfd.cStencilBits = 8;

        auto pixel_format = ::ChoosePixelFormat(dc, &pfd);
        game::ensure(pixel_format != 0, "failed to choose pixel format");

        game::ensure(::SetPixelFormat(dc, pixel_format, &pfd) == TRUE, "failed to set pixel format");

        const auto context = game::AutoRelease<HGLRC>{::wglCreateContext(dc), ::wglDeleteContext};
        game::ensure(context, "failed to create wgl context");

        game::ensure(::wglMakeCurrent(dc, context) == TRUE, "failed to make wgl context current");

        // Resolve WGL Functions
        resolve_gl_function(wglCreateContextAttribsARB, "wglCreateContextAttribsARB");
        resolve_gl_function(wglChoosePixelFormatARB, "wglChoosePixelFormatARB");

        game::ensure(::wglMakeCurrent(dc, 0) == TRUE, "could not unbind context");
    }

    auto resolve_global_gl_functions() -> void
    {
#define RESOLVE(TYPE, NAME) resolve_gl_function(NAME, #NAME);
        FOR_OPENGL_FUNCTIONS(RESOLVE)
    }

    auto setup_debug() -> void
    {
        ::glEnable(GL_DEBUG_OUTPUT);
        ::glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        ::glDebugMessageCallback(opengl_debug_callback, nullptr);
    }
}

namespace game
{
    Window::Window(std::uint32_t width, std::uint32_t height)
        : window_({}), dc_({}), wc_({})
    {
        wc_ = {};
        wc_.lpfnWndProc = window_proc;
        wc_.hInstance = ::GetModuleHandleA(nullptr);
        wc_.lpszClassName = "window class";
        wc_.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

        ensure(::RegisterClassA(&wc_) != 0, "failed to register class");

        ::RECT rect{};
        rect.left = {};
        rect.right = static_cast<int>(width);
        rect.top = {};
        rect.bottom = static_cast<int>(height);

        ensure(::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false) != 0, "could not resize window");

        window_ = {::CreateWindowExA(
                       0,                 // style
                       wc_.lpszClassName, // classname
                       "game window",
                       WS_OVERLAPPEDWINDOW,
                       CW_USEDEFAULT,
                       CW_USEDEFAULT,
                       rect.right - rect.left,
                       rect.bottom - rect.top,
                       nullptr,
                       nullptr,
                       wc_.hInstance,
                       nullptr),
                   ::DestroyWindow};

        dc_ = game::AutoRelease<::HDC>{
            ::GetDC(window_), [this](auto dc_)
            {
                ::ReleaseDC(window_, dc_);
            }};

        ::ShowWindow(window_, SW_SHOW);
        ::UpdateWindow(window_);

        resolve_wgl_functions(wc_.hInstance);

        init_opengl(dc_);
        resolve_global_gl_functions();
        setup_debug();
        ::glEnable(GL_DEPTH_TEST);
    }

    auto Window::pump_event() const -> std::optional<Event>
    {
        auto message = ::MSG{};
        while (::PeekMessageA(&message, nullptr, 0, 0, PM_REMOVE) != 0)
        {
            ::TranslateMessage(&message);
            ::DispatchMessageA(&message);
        }

        if (!std::ranges::empty(g_event_queue))
        {
            const auto event = g_event_queue.front();
            g_event_queue.pop();
            return event;
        }

        return {};
    }

    auto Window::swap() const -> void
    {
        ::SwapBuffers(dc_);
    }

}