#pragma once

#include <array>
#include <format>
#include <span>

#include "vector3.h"

namespace game
{
    class Matrix4
    {
    private:
        std::array<float, 16u> elements_;
        /* data */
    public:
        constexpr Matrix4()
            : elements_({1.0f, 0.0f, 0.0f, 0.0f,
                         0.0f, 1.0f, 0.0f, 0.0f,
                         0.0f, 0.0f, 1.0f, 0.0f,
                         0.0f, 0.0f, 0.0f, 1.0f})
        {
        }

        constexpr Matrix4(const std::array<float, 16u> &elements)
            : elements_(elements)
        {
        }

        constexpr Matrix4(const Vector3 &translation)
            : elements_({1.0f, 0.0f, 0.0f, 0.0f,
                         0.0f, 1.0f, 0.0f, 0.0f,
                         0.0f, 0.0f, 1.0f, 0.0f,
                         translation.x, translation.y, translation.z, 1.0f})
        {
        }

        auto lookAt(const Vector3 &eye, const Vector3 &lookAt, const Vector3 &up) -> Matrix4
        {
            const auto f = Vector3::normalise(lookAt - eye);
            const auto up_normalised = Vector3::normalise(up);

            const auto s = Vector3::normalise(Vector3::cross(f, up_normalised));
            const auto u = Vector3::normalise(Vector3::cross(s, f));

            auto m = Matrix4{};

            m.elements_ = {{s.x, u.x, -f.x, 0.0f,
                            s.y, u.y, -f.y, 0.0f,
                            s.z, u.z, -f.z, 0.0f,
                            0.0f, 0.0f, 0.0f, 1.0f}};

            return m * Matrix4(-eye);
        }

        auto perspective(float fov, float width, float height, float near_plane, float far_plane) -> Matrix4
        {
            Matrix4 m;

            const auto aspect_ratio = width / height;
            const auto tmp = std::tan(fov / 2.0f);
            const auto t = tmp * near_plane;
            const auto b = -t;
            const auto r = t * aspect_ratio;
            const auto l = b * aspect_ratio;

            m.elements_ = {
                {(2.0f * near_plane) / (r - l),
                 0.0f,
                 0.0f,
                 0.0f,
                 0.0f,
                 (2.0f * near_plane) / (t - b),
                 0.0f,
                 0.0f,
                 (r + l) / (r - l),
                 (t + b) / (t - b),
                 -(far_plane + near_plane) / (far_plane - near_plane),
                 -1.0f,
                 0.0f,
                 0.0f,
                 -(2.0f * far_plane * near_plane) / (far_plane - near_plane),
                 0.0f}};

            return m;
        }

        constexpr auto data() const -> std::span<const float>
        {
            return elements_;
        }

        friend constexpr auto operator*=(Matrix4 &m1, const Matrix4 &m2) -> Matrix4 &;
        friend constexpr auto operator*(const Matrix4 &m1, const Matrix4 &m2) -> Matrix4;
    };

    constexpr auto operator*=(Matrix4 &m1, const Matrix4 &m2) -> Matrix4 &
    {
        // multiple m1 by m2 (column major)

        Matrix4 result = {};
        for (auto i = 0u; i < 4u; ++i)
        {
            for (auto j = 0u; j < 4u; j++)
            {
                result.elements_[i + j * 4] = 0.f;
                for (auto k = 0u; k < 4u; ++k)
                {
                    result.elements_[i + j * 4] += m1.elements_[i + k * 4] * m2.elements_[k + j * 4];
                }
            }
        }

        m1 = result;
        return m1;
    }

    constexpr auto operator*(const Matrix4 &m1, const Matrix4 &m2) -> Matrix4
    {
        auto tmp{m1};
        return tmp *= m2;
    }

} // namespace game

template <>
struct std::formatter<game::Matrix4>
{
    constexpr auto parse(std::format_parse_context &ctx)
    {
        return std::begin(ctx);
    }

    auto format(const game::Matrix4 &obj, std::format_context &ctx) const
    {
        const auto *data = obj.data().data();
        return std::format_to(ctx.out(), "{} {} {} {}\n{} {} {} {}\n{} {} {} {}\n{} {} {} {}",
                              data[0],
                              data[1],
                              data[2],
                              data[3],
                              data[4],
                              data[5],
                              data[6],
                              data[7],
                              data[8],
                              data[9],
                              data[10],
                              data[11],
                              data[12],
                              data[13],
                              data[14],
                              data[15]);
    }
};
