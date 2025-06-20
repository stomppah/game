#include "entity.h"

#include <span>

#include "material.h"
#include "matrix4.h"
#include "mesh.h"
#include "vector3.h"

namespace game
{
    Entity::Entity(const Mesh *mesh, const Material *material, const Vector3 &position)
        : mesh_(mesh), material_(material), model_(Matrix4{position})
    {
    }

    auto Entity::mesh() const -> const Mesh *
    {
        return mesh_;
    }

    auto Entity::material() const -> const Material *
    {
        return material_;
    }

    auto Entity::model() const -> std::span<const float>
    {
        return model_.data();
    }
}