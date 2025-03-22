#include <print>
#include "window.h"

auto main() -> int
{
    std::println("hello world!");

    game::Window window{800u, 600u};

    while (window.running())
    {
        }

    return 0;
}