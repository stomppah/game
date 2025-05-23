#include "renderer.h"

#include "material.h"
#include "matrix4.h"
#include "mesh.h"
#include "opengl.h"
#include "vector3.h"

#include <numbers>

namespace game
{
    Renderer::Renderer(Material material)
        : mesh_{},
          material_(std::move(material))
    {
        ::glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }

    auto Renderer::render() const -> void
    {
        ::glClear(GL_COLOR_BUFFER_BIT);

        ::glUseProgram(material_.native_handle());

        static constexpr auto model = Matrix4{Vector3{.x = 0.0f, .y = 0.0f, .z = 0.0f}};
        const auto model_uniform = ::glGetUniformLocation(material_.native_handle(), "model");
        ::glUniformMatrix4fv(model_uniform, 1, GL_FALSE, model.data().data());

        static auto matrix = Matrix4{};
        static const auto view = matrix.lookAt(
            {.x = 0.5f, .y = 0.0f, .z = 5.0f},
            {.x = 0.0f, .y = 0.0f, .z = 0.0f},
            {.x = 0.0f, .y = 1.0f, .z = 0.0f});
        const auto view_uniform = ::glGetUniformLocation(material_.native_handle(), "view");
        ::glUniformMatrix4fv(view_uniform, 1, GL_FALSE, view.data().data());

        static auto proj = Matrix4{};
        proj = proj.perspective(std::numbers::pi_v<float> / 4.0f, 800.0f, 600.0f, 0.0001f, 100.0f);
        const auto proj_uniform = ::glGetUniformLocation(material_.native_handle(), "projection");
        ::glUniformMatrix4fv(proj_uniform, 1, GL_FALSE, proj.data().data());

        // draw
        mesh_.bind();
        ::glDrawArrays(GL_TRIANGLES, 0, 3);
        mesh_.unbind();
    }
}