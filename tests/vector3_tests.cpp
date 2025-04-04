#include <gtest/gtest.h>

#include "vector3.h"

using namespace game;

TEST(Vector3Test, Normalization) {
    Vector3 v{.x = 3.0f, .y = 0.0f, .z = 4.0f};  // 3-4-5 triangle
    auto normalized = Vector3::normalise(v);
    
    ASSERT_NEAR(normalized.x, 0.6f, 0.0001f);  // 3/5
    ASSERT_NEAR(normalized.y, 0.0f, 0.0001f);  // 0/5
    ASSERT_NEAR(normalized.z, 0.8f, 0.0001f);  // 4/5
}
