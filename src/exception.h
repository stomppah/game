#pragma once

#include <stdexcept>
#include <stacktrace>
#include <string>

namespace game
{
    class Exception : public std::runtime_error
    {
    public:
        Exception(const std::string &what);

        auto stacktrace() const -> std::string;

    private:
        /* data */
        std::stacktrace trace_;
    };

}