#include "../main.h"
#include "../Hacks/thirdperson.hpp"

void hkOverrideView(void* thisptr, CViewSetup& setup)
{
    
    auto* local = pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    if(vars.misc.enabled && vars.misc.fovt && vars.misc.fov > 0) {
        if(local && !local->IsScoped()) {
            setup.fov += vars.misc.fov;
        }

    
    if (pEngine->IsInGame() && local && local->GetAlive() && local->GetHealth() > 0)
    {   
        ThirdPerson::OverrideView(setup);
    }
    
    createmoveVMT->GetOriginalMethod<tOverrideView>(19)(thisptr, setup);
    }
}
