#include <print>
#include <format>
#include <stdexcept>
#include <iostream>

#include "window.h"
#include "exception.h"

auto main() -> int
{
    std::println("hello world!");

    try
    {
        game::Window window{800u, 600u};

        while (window.running())
        {
        }
    }
    catch (const game::Exception &err)
    {
        std::println(std::cerr, "{}", err);
    }
    catch (...)
    {
        std::println(std::cerr, "unknown exception");
    }

    return 0;
}