#pragma once
#include "main.h"


namespace GrenadePrediction
{
    extern float cameraHeight;
    // Hooks
    void OverrideView( CViewSetup* pSetup );
    void Paint();
    //void RenderView( void* thisptr, CViewSetup& setup, CViewSetup& hudViewSetup, unsigned int nClearFlags, int whatToDraw );
    void CreateMove( CUserCmd *cmd ); // For not allowing Jumps via Scroll wheel
}
