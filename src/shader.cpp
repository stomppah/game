#include "shader.h"

#include <format>
#include <string_view>

#include "auto_release.h"
#include "exception"
#include "opengl.h"

namespace game
{
    Shader::Shader(std::string_view source, ShaderType type)
        : handle_{}, type_(type)
    {
        }
}