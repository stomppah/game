#include "shader.h"

#include <string_view>

#include "auto_release.h"
#include "error.h"
#include "opengl.h"

namespace
{
    auto to_native(game::ShaderType type) -> ::GLenum
    {
        switch (type)
        {
            using enum game::ShaderType;
        case VERTEX:
            return GL_VERTEX_SHADER;
        case FRAGMENT:
            return GL_FRAGMENT_SHADER;
        default:
            break;
        }
        throw game::Exception("unknown shader type");
    }
}

namespace game
{
    Shader::Shader(std::string_view source, ShaderType type)
        : handle_{}, type_(type)
    {
        handle_ = game::AutoRelease<::GLuint>{
            ::glCreateShader(to_native(type)), ::glDeleteShader};

        const ::GLchar *strings[] = {source.data()};
        const ::GLint lengths[] = {static_cast<::GLint>(source.length())};

        ::glShaderSource(handle_, 1, strings, lengths);
        ::glCompileShader(handle_);

        ::GLint result{};
        ::glGetShaderiv(handle_, GL_COMPILE_STATUS, &result);

        game::ensure(result, "failed to compile shader");
    }

    auto Shader::type() const -> ShaderType
    {
        return type_;
    }
    auto Shader::native_handle() const -> ::GLuint
    {
        return handle_;
    }
}