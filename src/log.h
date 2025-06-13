#pragma once

#include <format>
#include <print>
#include <source_location>
#include <string_view>

namespace game::log
{
    enum class Level
    {
        DEBUG,
        INFO,
        WARN,
        ERR
    };

    template <Level L, class... Args>
    struct print
    {
    };

    template <Level L, class... Args>
    struct print<L, const char *, Args...>
    {
        print(const char *msg, const Args&... args, [[maybe_unused]] std::source_location loc = std::source_location::current())
        {
            auto c = "?";
            if constexpr (L == Level::DEBUG)
            {
                c = "DEBUG";
            }

            if constexpr (L == Level::INFO)
            {
                c = "INFO";
            }

            if constexpr (L == Level::WARN)
            {
                c = "WARN";
            }

            if constexpr (L == Level::ERR)
            {
                c = "ERROR";
            }

            std::println("[{}] {}:{} {}", c, loc.file_name(), loc.line(),
                         std::vformat(msg,
                                      std::make_format_args(args...)));
        }
    };

    template <Level L, class... Args>
    print(Args...) -> print<L, Args...>;

    template <class... Args>
    using debug = print<Level::DEBUG, Args...>;

    template <class... Args>
    using info = print<Level::INFO, Args...>;

    template <class... Args>
    using warn = print<Level::WARN, Args...>;

    template <class... Args>
    using error = print<Level::ERR, Args...>;
}

