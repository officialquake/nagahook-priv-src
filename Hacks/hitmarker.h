#pragma once

#include "../main.h"
#include "../SDK/GameEvent.h"

namespace Hitmarkers
{
    //Hooks
    void FireGameEvent(IGameEvent* event);
    void Paint();
}
