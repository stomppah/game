#include "key_event.h"

#include "key.h"

namespace game
{
    KeyEvent::KeyEvent(Key key) : key_(key) {}

    auto KeyEvent::key() const -> Key
    {
        return key_;
    }
}