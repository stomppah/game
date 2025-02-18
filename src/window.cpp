#include "window.h"

#include <cstdint>

#include <Windows.h>

#include "auto_release.h"
#include <stdexcept>

namespace game
{
    Window::Window(std::uint32_t width, std::uint32_t height)
        : window_({}), wc_({})
    {
        wc_ = {};
        wc_.lpfnWndProc = ::DefWindowProcA,
        wc_.hInstance = ::GetModuleHandleA(nullptr),
        wc_.lpszClassName = "window class",
        wc_.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

        if (::RegisterClassA(&wc_) == 0)
        {
            throw std::runtime_error("failed to register class!");
        }

        ::RECT rect{};
        rect.left = {};
        rect.right = static_cast<int>(width);
        rect.top = {};
        rect.bottom = static_cast<int>(height);

        if (::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false) == 0)
        {
            throw std::runtime_error("could not resize window");
        }

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
}