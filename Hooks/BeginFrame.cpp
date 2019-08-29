#include "main.h"

void hkBeginFrame(void* thisptr, float frameTime)
{
    
    
    return materialVMT->GetOriginalMethod<BeginFrameFn>(42)(thisptr, frameTime);
}
