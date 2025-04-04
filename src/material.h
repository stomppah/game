#pragma once

#include "opengl.h"
#include "shader.h"
#include "auto_release.h"

namespace game
{

    class Material
    {
    public:
        Material(const Shader &vertex_shader, const Shader &fragment_shader);
        // ~Material();
        auto native_handle() const -> ::GLuint;

    private:
        /* data */
        AutoRelease<::GLuint> handle_;
    };

    // Material::Material(/* args */)
    // {
    // }

    // Material::~Material()
    // {
    // }

}