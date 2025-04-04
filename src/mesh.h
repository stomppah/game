#pragma once

#include "auto_release.h"
#include "opengl.h"

namespace game
{
    class Mesh
    {
    public:
        Mesh();
        auto bind() const -> void;
        auto unbind() const -> void;

    private:
        AutoRelease<::GLuint> vao_;
        AutoRelease<::GLuint> vbo_;
    };

}