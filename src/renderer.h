#pragma once

#include "mesh.h"
#include "material.h"

namespace game
{
    class Renderer
    {
    public:
        Renderer(Material material);
        auto render() const -> void;

    private:
        Mesh mesh_;
        Material material_;
    };

}