#include <print>
#include <format>
#include <stdexcept>
#include <iostream>

#include "auto_release.h"
#include "error.h"
#include "exception.h"
#include "log.h"
#include "material.h"
#include "mesh.h"
#include "renderer.h"
#include "shader.h"
#include "window.h"

namespace
{
    static constexpr auto vertex_shader_src = R"(
#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 colour;

out vec3 vertex_colour;

void main()
{
gl_Position = vec4(position, 1.0);
vertex_colour = colour;
}
)";

    static constexpr auto fragment_shader_src = R"(
#version 460 core

in vec3 vertex_colour;
out vec4 frag_colour;

void main()
{
frag_colour = vec4(vertex_colour, 1.0);
}
)";

}

auto main() -> int
{
    game::log::info("hello world!");

    try
    {
        game::Window window{800u, 600u};

        // create shaders
        const auto vertex_shader = game::Shader{vertex_shader_src, game::ShaderType::VERTEX};
        const auto fragment_shader = game::Shader{fragment_shader_src, game::ShaderType::FRAGMENT};
        auto material = game::Material{vertex_shader, fragment_shader};

        const auto renderer = game::Renderer{std::move(material)};

        while (window.running())
        {
            renderer.render();
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