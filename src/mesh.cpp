#include "mesh.h"

#include "opengl.h"
#include "auto_release.h"
#include "vertex_data.h"

namespace
{
    static constexpr game::VertexData vertex_data[] = {
        {.position = {.x = 0.0f, .y = 0.5f, .z = 0.0f}, .colour = {.r = 1.0f, .g = 0.0f, .b = 0.0f}},
        {.position = {.x = -0.5f, .y = -0.5f, .z = 0.0f}, .colour = {.r = 0.0f, .g = 1.0f, .b = 0.0f}},
        {.position = {.x = 0.5f, .y = -0.5f, .z = 0.0f}, .colour = {.r = 0.0f, .g = 0.5f, .b = 1.0f}}};
}

namespace game
{

    Mesh::Mesh()
        : vao_{0u, [](auto vao)
               { ::glDeleteVertexArrays(1, &vao); }},
          vbo_{0u, [](auto vbo)
               { ::glDeleteBuffers(1, &vbo); }}
    {
        ::glGenVertexArrays(1, &vao_);

        ::glGenBuffers(1, &vbo_);

        bind();

        ::glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        ::glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);

        ::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void *>(0));
        ::glEnableVertexAttribArray(0);
        ::glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void *>(3 * sizeof(float)));
        ::glEnableVertexAttribArray(1);

        unbind();
    }

    auto Mesh::bind() const -> void
    {
        ::glBindVertexArray(vao_);
    }
    auto Mesh::unbind() const -> void
    {
        ::glBindVertexArray(0);
    }
}