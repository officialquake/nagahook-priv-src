#include "thirdperson.hpp"


static Vector GetDesiredCameraOffset()
{
    ConVar* cam_idealdist = pCvar->FindVar("cam_idealdist");
    ConVar* cam_idealdistright = pCvar->FindVar("cam_idealdistright");
    ConVar* cam_idealdistup = pCvar->FindVar("cam_idealdistup");
    
    return Vector(cam_idealdist->GetFloat(), cam_idealdistright->GetFloat(), cam_idealdistup->GetFloat());
}

void ThirdPerson::OverrideView(CViewSetup& pSetup)
{
    if(!vars.misc.thirdperson) {
        pInput->m_fCameraInThirdPerson = false;
        pInput->m_vecCameraOffset.z = 150.0f;
        return;
    }
    
    
    //float distance = 100.f;
    
    C_BaseEntity *localplayer = (C_BaseEntity*)pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    if(!localplayer || !localplayer->GetAlive())
        return;
    if(!pEngine->IsInGame())
        return;
    
    if(localplayer->GetHealth() > 0 && vars.misc.thirdperson){
        
        
        QAngle *view = localplayer->GetViewwAngles();
        trace_t tr;
        Ray_t ray;
        
        ray.Init(localplayer->GetEyePosition(), (localplayer->GetEyePosition() - GetDesiredCameraOffset()));
        CTraceFilter traceFilter;
        traceFilter.pSkip = localplayer;
        pEngineTrace->TraceRay(ray, MASK_SHOT, &traceFilter, &tr);
        
        Vector diff = localplayer->GetEyePosition() - tr.endpos;
        
        float distance2D = diff.Length2D();
        
        bool horOK = distance2D > (vars.misc.tpoffset - 2.0f);
        bool vertOK = (abs(diff.z) - abs(GetDesiredCameraOffset().z) < 3.0f);
        
        float cameraDistance;
        
        if( horOK && vertOK )  // If we are clear of obstacles
        {
            cameraDistance= vars.misc.tpoffset; // go ahead and set the distance to the setting
        }
        else
        {
            if( vertOK ) // if the Vertical Axis is OK
            {
                cameraDistance = distance2D * 0.95f;
            }
            else// otherwise we need to move closer to not go into the floor/ceiling
            {
                cameraDistance = abs(diff.z) * 0.95f;
            }
        }
        
        Vector origin = localplayer->GetVecOrigin() + localplayer->GetVecViewOffset(); // Origin angles which we're seeing
        pEngine->GetViewAngles(origin);
        
        pInput->m_fCameraInThirdPerson = true;
        pInput->m_vecCameraOffset.x = origin.x;
        pInput->m_vecCameraOffset.y = origin.y;
        pInput->m_vecCameraOffset.z = cameraDistance;
    }
}


