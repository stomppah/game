#pragma once

#include <span>

#include "matrix4.h"
#include "vector3.h"

namespace game
{

    class Camera
    {
    public:
        Camera(
            const Vector3 &position,
            const Vector3 &look_at,
            const Vector3 &up,
            float fov,
            float width,
            float height,
            float near_plane,
            float far_plane);

        auto view() const -> std::span<const float>;
        auto projection() const -> std::span<const float>;
        // ~Camera();

    private:
        Matrix4 view_;
        Matrix4 projection_;
    };

    // Camera::Camera(/* args */)
    // {
    // }

    // Camera::~Camera()
    // {
    // }

}