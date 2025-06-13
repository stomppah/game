#include <format>
#include <iostream>
#include <numbers>
#include <print>
#include <stdexcept>

#include "auto_release.h"
#include "camera.h"
#include "entity.h"
#include "error.h"
#include "exception.h"
#include "log.h"
#include "material.h"
#include "matrix4.h"
#include "mesh.h"
#include "renderer.h"
#include "scene.h"
#include "shader.h"
#include "window.h"

namespace
{
    static constexpr auto vertex_shader_src = R"(
#version 460 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 colour;

out vec3 vertex_colour;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
gl_Position = projection * view * model * vec4(position, 1.0);
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
        const auto mesh = game::Mesh{};
        const auto renderer = game::Renderer{};
        const auto entity = game::Entity{&mesh, &material, game::Vector3{.x = 0.0f, .y = -1.0f, .z = 0.0f}};
        const auto entity1 = game::Entity{&mesh, &material, game::Vector3{.x = -3.0f, .y = -1.0f, .z = 0.0f}};
        const auto entity2 = game::Entity{&mesh, &material, game::Vector3{.x = 3.0f, .y = -1.0f, .z = 0.0f}};
        const auto entity3 = game::Entity{&mesh, &material, game::Vector3{.x = 0.0f, .y = 2.0f, .z = 0.0f}};
        const auto entity4 = game::Entity{&mesh, &material, game::Vector3{.x = -3.0f, .y = 2.0f, .z = 0.0f}};
        const auto entity5 = game::Entity{&mesh, &material, game::Vector3{.x = 3.0f, .y = 2.0f, .z = 0.0f}};

        auto scene = game::Scene{
            .entities{&entity, &entity1, &entity2, &entity3, &entity4, &entity5}};

        const auto camera = game::Camera{
            {.x = 3.0f, .y = 0.0f, .z = 5.0f},
            {.x = 0.0f, .y = 0.0f, .z = 0.0f},
            {.x = 0.0f, .y = 1.0f, .z = 0.0f},
            std::numbers::pi_v<float> / 4.0f,
            800.0f,
            600.0f,
            0.1f,
            100.0f};

        while (window.running())
        {
            renderer.render(camera, scene);
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