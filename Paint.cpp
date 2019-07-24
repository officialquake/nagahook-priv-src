/*      Paint.cpp
 *
 *  I'll use this at some point
 *  [Sig needed for StartDrawing and FinishDrawing] [vguimatsurface_client]
 */

#include "main.h"
#include "Hacks/hitmarker.h"
#include "Drawings/menu.h"
// Hacks


void Paint_hk(void* thisptr, PaintMode_t mode)
{
    engineVGuiVMT->GetOriginalMethod<oPaint>(15)(thisptr, mode);
    
    
        Hitmarkers::Paint();
}

