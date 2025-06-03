#pragma once

#include "camera.h"
#include "mesh.h"
#include "material.h"

namespace game
{
    class Renderer
    {
    public:
        Renderer(Material material);
        auto render(const Camera &camera) const -> void;

    private:
        Mesh mesh_;
        Material material_;
    };

}