#pragma once

#include <format>
#include <string_view>

#include "exception.h"

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

}