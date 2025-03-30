#include <print>
#include <format>
#include <stdexcept>
#include <iostream>

#include "window.h"
#include "exception.h"
#include "opengl.h"
#include "auto_release.h"

namespace
{
    static constexpr auto vertex_shader = R"(
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

    static constexpr auto fragment_shader = R"(
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

    auto compile_shader(std::string_view source, ::GLenum shader_type) -> game::AutoRelease<::GLuint>
    {
        auto shader = game::AutoRelease<::GLuint>{
            ::glCreateShader(shader_type), ::glDeleteShader};

        const ::GLchar *strings[] = {source.data()};
        const ::GLint lengths[] = {static_cast<::GLint>(source.length())};
        ::glShaderSource(shader, 1, strings, lengths);
        return shader;
    }

}

int main()
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
