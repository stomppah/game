#pragma once

#include <format>
#include <string_view>

using namespace std::literals;

namespace game
{
    enum class Key
    {
        A = 0x41,
        B = 0x42,
        C = 0x43,
        D = 0x44,
        E = 0x45,
        F = 0x46,
        G = 0x47,
        H = 0x48,
        I = 0x49,
        J = 0x4A,
        K = 0x4B,
        L = 0x4C,
        M = 0x4D,
        N = 0x4E,
        O = 0x4F,
        P = 0x50,
        Q = 0x51,
        R = 0x52,
        S = 0x53,
        T = 0x54,
        U = 0x55,
        V = 0x56,
        W = 0x57,
        X = 0x58,
        Y = 0x59,
        Z = 0x5A,
        UP = 0x26,
        DOWN = 0x28,
        LEFT = 0x25,
        RIGHT = 0x27,
        ESC = 0x1B
    };
}

template <>
struct std::formatter<game::Key>
{
    constexpr auto parse(std::format_parse_context &ctx)
    {
        return std::begin(ctx);
    }

    auto format(const game::Key &obj, std::format_context &ctx) const
    {
        auto s = "?"sv;

        switch (obj)
        {
        case game::Key::A:
            s = "A"sv;
            break;
        case game::Key::B:
            s = "B"sv;
            break;
        case game::Key::C:
            s = "C"sv;
            break;
        case game::Key::D:
            s = "D"sv;
            break;
        case game::Key::E:
            s = "E"sv;
            break;
        case game::Key::F:
            s = "F"sv;
            break;
        case game::Key::G:
            s = "G"sv;
            break;
        case game::Key::H:
            s = "H"sv;
            break;
        case game::Key::I:
            s = "I"sv;
            break;
        case game::Key::J:
            s = "J"sv;
            break;
        case game::Key::K:
            s = "K"sv;
            break;
        case game::Key::L:
            s = "L"sv;
            break;
        case game::Key::M:
            s = "M"sv;
            break;
        case game::Key::N:
            s = "N"sv;
            break;
        case game::Key::O:
            s = "O"sv;
            break;
        case game::Key::P:
            s = "P"sv;
            break;
        case game::Key::Q:
            s = "Q"sv;
            break;
        case game::Key::R:
            s = "R"sv;
            break;
        case game::Key::S:
            s = "S"sv;
            break;
        case game::Key::T:
            s = "T"sv;
            break;
        case game::Key::U:
            s = "U"sv;
            break;
        case game::Key::V:
            s = "V"sv;
            break;
        case game::Key::W:
            s = "W"sv;
            break;
        case game::Key::X:
            s = "X"sv;
            break;
        case game::Key::Y:
            s = "Y"sv;
            break;
        case game::Key::Z:
            s = "Z"sv;
            break;
        case game::Key::UP:
            s = "UP"sv;
            break;
        case game::Key::DOWN:
            s = "DOWN"sv;
            break;
        case game::Key::LEFT:
            s = "LEFT"sv;
            break;
        case game::Key::RIGHT:
            s = "RIGHT"sv;
            break;
        case game::Key::ESC:
            s = "ESC"sv;
            break;

        default:
            break;
        }

        return std::format_to(ctx.out(), "{}", s);
    }
};