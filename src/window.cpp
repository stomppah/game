#include "window.h"

#include <cstdint>
#include <print>
#include <Windows.h>
#include <stdexcept>

#include "auto_release.h"
#include "error.h"

namespace
{
    auto g_running = true;

    auto CALLBACK window_proc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) -> LRESULT
    {
        switch (Msg)
        {
        case WM_CLOSE:
            g_running = false;
            break;
        case WM_KEYDOWN:
            std::println("key down");
            break;

        default:
            break;
        };

        return ::DefWindowProcA(hWnd, Msg, wParam, lParam);
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
    }
}

namespace game
{
    Window::Window(std::uint32_t width, std::uint32_t height)
        : window_({}), wc_({})
    {
        wc_ = {};
        wc_.lpfnWndProc = window_proc,
        wc_.hInstance = ::GetModuleHandleA(nullptr),
        wc_.lpszClassName = "window class",
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

        ::ShowWindow(window_, SW_SHOW);
        ::UpdateWindow(window_);

        // Resolve WGL Functions
        // init opengl
    }

    auto Window::running() const -> bool
    {
        auto message = ::MSG{};
        while (::PeekMessageA(&message, nullptr, 0, 0, PM_REMOVE) != 0)
        {
            ::TranslateMessage(&message);
            ::DispatchMessageA(&message);
        }

        return g_running;
    }

}