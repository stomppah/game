#include <gtest/gtest.h>

#include "matrix4.h"
#include "vector3.h"

#include <numbers>

using namespace game;

TEST(Matrix4Test, multiply)
{
    const auto m1 = game::Matrix4{{1.0f, 2.0f, 3.0f, 4.0f,
                                   1.0f, 2.0f, 3.0f, 4.0f,
                                   1.0f, 2.0f, 3.0f, 4.0f,
                                   1.0f, 2.0f, 3.0f, 4.0f}};
    const auto m2 = game::Matrix4{};

    ASSERT_EQ(m1 * m2, m1);
}

TEST(Matrix4Test, lookAt)
{
    game::Matrix4 matrix;
    const auto view = matrix.lookAt(
        {.x = 1.0f, .y = 0.0f, .z = 5.0f},
        {.x = 0.0f, .y = 0.0f, .z = 0.0f},
        {.x = 0.0f, .y = 1.0f, .z = 0.0f});

    const auto expected = game::Matrix4{
        {0.980581f, 0.000000f, 0.196116f, 0.000000f, 0.000000f, 1.000000f, -0.000000f, 0.000000f, -0.196116f, 0.000000f, 0.980581f, 0.000000f, -0.000000f, -0.000000f, -5.099020f, 1.000000f}};

    const auto view_spn = view.data();
    const auto expected_spn = expected.data().data();

    for (auto i = 0u; i < 16u; ++i)
    {
        ASSERT_NEAR(view_spn[i], expected_spn[i], 0.001f);
    }
}

TEST(Matrix4Test, perspective)
{
    game::Matrix4 matrix;

    const auto expected = game::Matrix4{
        {1.810660f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, 2.414213f, 0.000000f, 0.000000f, 0.000000f, 0.000000f, -1.002002f, -1.000000f, 0.000000f, 0.000000f, -0.200200f, 0.000000f}};

    const auto proj = matrix.perspective(std::numbers::pi_v<float> / 4.0f, 800.0f, 600.0f, 0.1f, 100.0f);

    const auto spn = proj.data();
    const auto expected_spn = expected.data().data();

    for (auto i = 0u; i < 16u; ++i)
    {
        ASSERT_NEAR(spn[i], expected_spn[i], 0.001f);
    }
}