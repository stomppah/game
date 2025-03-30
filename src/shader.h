#pragma once

#include <string_view>
#include <string>
#include <format>
#include <stdexcept>
#include <cstdint>

#include "auto_release.h"
#include "exception.h"
#include "opengl.h"

namespace game
{
    enum class ShaderType
    {
        VERTEX,
        FRAGMENT
    };

    class Shader
    {
    public:
        Shader(std::string_view source, ShaderType type);
        auto type() const -> ShaderType;
        auto native_handle() const -> ::GLuint;

    private:
        AutoRelease<::GLuint> handle_;
        ShaderType type_;
    };
}
template <>
struct std::formatter<game::ShaderType>
{
    constexpr auto parse(std::format_parse_context &ctx)
    {
        return std::begin(ctx);
    }

    auto format(const game::Shader &obj, std::format_context &ctx) const
    {
        switch (obj.type())
        {
            using enum game::ShaderType;
        case VERTEX:
            return std::format_to(ctx.out(), "VERTEX");
        case FRAGMENT:
            return std::format_to(ctx.out(), "FRAGMENT");
        default:
            break;
        }
        throw game::Exception("unknown shader type");
    }
};
