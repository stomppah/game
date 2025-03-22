#pragma once

#include <format>
#include <string_view>

#include "exception.h"
#include "auto_release.h"

namespace game
{

    template <class... Args>
    auto ensure(bool predicate, std::string_view msg, Args &&...args) -> void
    {
        if (!predicate)
        {
            throw Exception(std::vformat(msg, std::make_format_args(std::forward(args)...)), 2u);
        }
    }

    template <class T, T Invalid, class... Args>
    auto ensure(AutoRelease<T, Invalid> &obj, std::string_view msg, Args &&...args) -> void
    {
        ensure(!!obj, msg, std::forward(args)...);
    }
}