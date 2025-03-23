#include <print>
#include <format>
#include <stdexcept>
#include <iostream>

#include "window.h"
#include "exception.h"
#include "opengl.h"

auto main() -> int
{
    std::println("hello world!");

    try
    {
        game::Window window{800u, 600u};

        while (window.running())
        {
            static auto b = 1.0f;
            static auto inc = -0.001f;

            b += inc;
            if ((b <= 0.0f) || (b >= 1.0f))
            {
                inc *= -1.0f;
            }

            ::glClearColor(0.0f, 0.5f, b, 1.0f);

            ::glClear(GL_COLOR_BUFFER_BIT);

            window.swap();
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