#include "../main.h"
#include "../Hacks/skinchanger.h"

bool hkFireEventClientSide(void* thisptr, IGameEvent* event){
    
    skinchanger->FireEventClientSide(event);

    return game_event_vmt->GetOriginalMethod<tFireGameEvent>(10)(thisptr, event);
}
