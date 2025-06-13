#pragma once

#include "camera.h"
#include "scene.h"

namespace game
{
    class Renderer
    {
    public:
        auto render(const Camera &camera, const Scene &scene) const -> void;

    private:
    };

}