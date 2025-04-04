#include "material.h"

#include "opengl.h"
#include "shader.h"
#include "auto_release.h"
#include "error.h"

namespace game
{
    Material::Material(const Shader &vertex_shader, const Shader &fragment_shader)
        : handle_{}
    {
        ensure(vertex_shader.type() == ShaderType::VERTEX, "not a vertex shader");
        ensure(fragment_shader.type() == ShaderType::FRAGMENT, "not a fragment shader");

        // create program
        handle_ = game::AutoRelease<::GLuint>{
            ::glCreateProgram(),
            ::glDeleteProgram};
        ensure(handle_, "failed to create opengl program");

        // link shaders and program
        ::glAttachShader(handle_, vertex_shader.native_handle());
        ::glAttachShader(handle_, fragment_shader.native_handle());
        ::glLinkProgram(handle_);
    }

    auto Material::native_handle() const -> ::GLuint
    {
        return handle_;
    }
}