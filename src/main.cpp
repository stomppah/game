#include <print>
#include <format>
#include <stdexcept>
#include <iostream>

#include "window.h"
#include "exception.h"
#include "error.h"
#include "opengl.h"
#include "auto_release.h"

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

    auto compile_shader(std::string_view source, ::GLenum shader_type) -> game::AutoRelease<::GLuint>
    {
        auto shader = game::AutoRelease<::GLuint>{
            ::glCreateShader(shader_type), ::glDeleteShader};

        const ::GLchar *strings[] = {source.data()};
        const ::GLint lengths[] = {static_cast<::GLint>(source.length())};

        ::glShaderSource(shader, 1, strings, lengths);
        ::glCompileShader(shader);

        ::GLint result{};
        ::glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

        game::ensure(result, "failed to compile shader {}", shader_type);

        return shader;
    }

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
        auto vertex_shader = compile_shader(vertex_shader_src, GL_VERTEX_SHADER);
        auto fragment_shader = compile_shader(fragment_shader_src, GL_FRAGMENT_SHADER);

        // create program
        auto program = game::AutoRelease<::GLuint>{
            ::glCreateProgram(),
            ::glDeleteProgram};
        game::ensure(program, "failed to create opengl program");

        // link shaders and program
        ::glAttachShader(program, vertex_shader);
        ::glAttachShader(program, fragment_shader);
        ::glLinkProgram(program);

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
            ::glUseProgram(program);
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