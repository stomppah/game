#include "exception.h"

#include <format>
#include <sstream>

namespace game
{
    Exception::Exception(const std::string &what, std::uint32_t skip)
        : std::runtime_error(what), trace_(std::stacktrace::current(skip))
    {
    }

    auto Exception::stacktrace() const -> std::string
    {
        std::stringstream ss;
        ss << trace_;
        return ss.str();
    }
}