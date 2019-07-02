#include "../main.h"
#include "../Hacks/thirdperson.hpp"

void hkOverrideView(void* thisptr, CViewSetup& setup)
{
    
    auto* local = pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    if(vars.misc.enabled && vars.misc.fov > 0) {
        if(local && !local->IsScoped()) {
            setup.fov += vars.misc.fov;
        }

    
    if (!vars.misc.antiscreenshot || !pEngine->IsTakingScreenshot())
    {   
        ThirdPerson::OverrideView(setup);
    }
    
    createmoveVMT->GetOriginalMethod<tOverrideView>(19)(thisptr, setup);
}
}
