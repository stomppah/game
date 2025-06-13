#include "entity.h"

#include <span>

#include "material.h"
#include "matrix4.h"
#include "mesh.h"

namespace game
{
    Entity::Entity(const Mesh *mesh, const Material *material)
        : mesh_(mesh), material_(material), model_()
    {
    }

    auto Entity::model() const -> std::span<const float>
    {
        return model_.data();
    }
}