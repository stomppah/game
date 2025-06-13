#pragma once

#include <span>

#include "material.h"
#include "matrix4.h"
#include "mesh.h"

namespace game
{
    class Entity
    {

    public:
        Entity(const Mesh *mesh, const Material *material);

        auto model() const -> std::span<const float>;

    private:
        /* data */
        const Mesh *mesh_;
        const Material *material_;
        Matrix4 model_;
    };
}