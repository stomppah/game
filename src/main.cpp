#include <print>
#include <stdexcept>
#include <iostream>

#include "window.h"
#include "exception.h"

auto bar() -> void
{
    throw game::Exception("err");
}

auto foo() -> void
{
    bar();
}

auto main() -> int
{
    std::println("hello world!");

    try
    {
        foo();
    }
    catch (game::Exception &err)
    {
        std::println(std::cerr, "exception {} {}", err.what(), err.stacktrace());
    }

    // game::Window window{800u, 600u};

    // while (window.running())
    // {
    // }

    return 0;
}