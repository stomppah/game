#pragma once

#include "key_event.h"
#include "stop_event.h"

#include <variant>

namespace game
{
    using Event = std::variant<StopEvent, KeyEvent>;
}