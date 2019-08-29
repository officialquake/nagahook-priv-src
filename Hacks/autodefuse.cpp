//
//  autodefuse.cpp
//  vHook
//
//  Created by Timothy Dillan on 28/8/19.
//  Copyright © 2019 ViKiNG. All rights reserved.
//

#include "autodefuse.hpp"
void AutoDefuse::CreateMove(CUserCmd *cmd)
{
    if (!vars.aimbot.autodefuse && vars.aimbot.defusesilent)
        return;
    
    C_BasePlayer* localplayer = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    if (!localplayer || !localplayer->GetAlive())
        return;
    
    if (localplayer->GetTeam() != TeamID::TEAM_COUNTER_TERRORIST)
        return;
    
    C_BasePlantedC4* bomb = nullptr;
    
    for (int i = 1; i < pEntList->GetHighestEntityIndex(); i++)
    {
        C_BaseEntity* entity = pEntList->GetClientEntity(i);
        if (!entity)
            continue;
        
        if (entity->GetClientClass()->m_ClassID == EClassIds::CPlantedC4)
        {
            bomb = (C_BasePlantedC4*) entity;
            break;
        }
    }
    
    if (!bomb || bomb->IsBombDefused())
        return;
    
    float bombTimer = bomb->GetBombTime() - pGlobals->curtime;
    
    if (vars.aimbot.defusesilent)
    {
        float distance = localplayer->GetVecOrigin().DistTo(bomb->GetVecOrigin());
        if (cmd->buttons & IN_USE && distance <= 75.0f)
        {
            Vector pVecTarget = localplayer->GetEyePosition();
            Vector pTargetBomb = bomb->GetVecOrigin();
            Vector angle = CalcAngle(pVecTarget, pTargetBomb);
            ClampAngles(angle);
            cmd->viewangles = angle;
        }
    }
    else
        if (vars.aimbot.autodefuse)
        {
            if (localplayer->HasDefuser() && bombTimer > 5.5f)
                return;
            
            if (!localplayer->HasDefuser() && bombTimer > 10.5f)
                return;
            
            float distance = localplayer->GetVecOrigin().DistTo(bomb->GetVecOrigin());
            if (distance <= 75.0f)
                cmd->buttons |= IN_USE;
        }
}
