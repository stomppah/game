#pragma once

#include "key.h"

namespace game
{
    class KeyEvent
    {
    public:
        explicit KeyEvent(Key key);
        auto key() const -> Key;

    private:
        Key key_;
    };

}