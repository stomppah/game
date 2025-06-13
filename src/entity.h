#pragma once

#include <span>

#include "matrix4.h"

namespace game
{
    class Material;
    class Mesh;

    class Entity
    {

    public:
        Entity(const Mesh *mesh, const Material *material);

        auto mesh() const -> const Mesh *;
        auto material() const -> const Material *;
        auto model() const -> std::span<const float>;

    private:
        /* data */
        const Mesh *mesh_;
        const Material *material_;
        Matrix4 model_;
    };
}