#include "renderer.h"

#include "material.h"
#include "matrix4.h"
#include "mesh.h"
#include "opengl.h"
#include "vector3.h"

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

        static constexpr auto transform = Matrix4{Vector3{.x = 0.5f, .y = 0.0f, .z = 0.0f}};
        const auto transform_uniform = ::glGetUniformLocation(material_.native_handle(), "transform");
        ::glUniformMatrix4fv(transform_uniform, 1, GL_FALSE, transform.data().data());

        // draw
        mesh_.bind();
        ::glDrawArrays(GL_TRIANGLES, 0, 3);
        mesh_.unbind();
    }
}