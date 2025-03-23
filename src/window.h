#pragma once

#include <cstdint>

#include <Windows.h>

#include "auto_release.h"

namespace game
{

    class Window
    {
    private:
        AutoRelease<::HWND, nullptr> window_;
        AutoRelease<::HDC> dc_;
        WNDCLASSA wc_; // WEIRD WINDOWS STUFF
    public:
        Window(std::uint32_t width, std::uint32_t height);
        ~Window() = default;

        Window(const Window &) = delete;
        auto operator=(const Window &) -> Window & = delete;

        Window(Window &&) = delete;
        auto operator=(Window &&) -> Window & = delete;

        auto running() const -> bool;
    };
}