#include <print>
#include <format>
#include <stdexcept>
#include <iostream>

#include "window.h"
#include "exception.h"
#include "error.h"
#include "opengl.h"
#include "auto_release.h"
#include "shader.h"
#include "material.h"

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
    std::println("hello world!");

    static constexpr float vertex_data[] = {
        0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f,   //
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, //
        0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 1.0f}; //

    try
    {
        game::Window window{800u, 600u};

        // create shaders
        auto vertex_shader = game::Shader{vertex_shader_src, game::ShaderType::VERTEX};
        auto fragment_shader = game::Shader{fragment_shader_src, game::ShaderType::FRAGMENT};

        auto material = game::Material{vertex_shader, fragment_shader};

        ::glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        // create VAO
        auto vao = ::GLuint{};
        ::glGenVertexArrays(1, &vao);

        // create VBO
        auto vbo = ::GLuint{};
        ::glGenBuffers(1, &vbo);

        ::glBindVertexArray(vao);

        ::glBindBuffer(GL_ARRAY_BUFFER, vbo);
        ::glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);

        ::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void *>(0));
        ::glEnableVertexAttribArray(0);
        ::glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void *>(3 * sizeof(float)));
        ::glEnableVertexAttribArray(1);

        ::glBindVertexArray(0);

        // set it all up

        while (window.running())
        {
            ::glClear(GL_COLOR_BUFFER_BIT);

            // draw
            ::glUseProgram(material.native_handle());
            ::glBindVertexArray(vao);
            ::glDrawArrays(GL_TRIANGLES, 0, 3);

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