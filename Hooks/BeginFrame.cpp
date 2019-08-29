#include "main.h"
#include "../Hacks/namestealer.hpp"
void hkBeginFrame(void* thisptr, float frameTime)
{
    NameStealer::BeginFrame(frameTime);
    
    return materialVMT->GetOriginalMethod<BeginFrameFn>(42)(thisptr, frameTime);
}
