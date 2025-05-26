#pragma once

#include <cmath>

namespace game
{

    struct Vector3
    {
        static auto normalise(const Vector3 &v) -> Vector3
        {
            const auto length = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
            auto tmp = Vector3{.x = v.x / length, .y = v.y / length, .z = v.z / length};
            return tmp;
        }

        static constexpr auto cross(const Vector3 &v1, const Vector3 &v2) -> Vector3
        {
            const auto i = (v1.y * v2.z) - (v1.z * v2.y);
            const auto j = (v1.x * v2.z) - (v1.z * v2.x);
            const auto k = (v1.x * v2.y) - (v1.y * v2.x);

            return Vector3{.x = i, .y = -j, .z = k};
        }

        constexpr auto operator==(const Vector3 &) const -> bool = default;

        float x;
        float y;
        float z;
    };

    constexpr auto operator-=(Vector3 &v1, const Vector3 &v2) -> Vector3 &
    {
        v1.x -= v2.x;
        v1.y -= v2.y;
        v1.z -= v2.z;

        return v1;
    }

    constexpr auto operator-(const Vector3 &v1, const Vector3 &v2) -> Vector3
    {
        auto tmp = v1;
        return tmp -= v2;
    }

    constexpr auto operator-(const Vector3 &v) -> Vector3
    {
        return {-v.x, -v.y, -v.z};
    }

}