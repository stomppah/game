#pragma once

#include <vector>

namespace game
{
    class Entity;
    struct Scene
    {
        std::vector<const Entity *> entities;
    };
}