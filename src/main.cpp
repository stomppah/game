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

        ::glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        // create shaders
        // create program
        // link shaders and program
        // create VAO
        // create VBO
        // set it all up

        while (window.running())
        {
            ::glClear(GL_COLOR_BUFFER_BIT);

            // draw

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