#include "main.h"
// Hacks
#include "Hacks/hitmarker.h"

bool FireEvent_hk(void* thisptr, IGameEvent* event, bool bDontBroadcast) {
    if(event) {
        hitmarker->FireEvent(event);
    }
    return game_event_vmt->GetOriginalMethod<oFireEvent>(9)(thisptr, event, bDontBroadcast);
}
