#include "window.h"

#include <cstdint>
#include <print>
#include <Windows.h>
#include <stdexcept>

#include "auto_release.h"
#include "error.h"

namespace game
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