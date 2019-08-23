#include "EnginePrediction.h"
#include "../Utils/checksum_md5.h"


//
//  PredictionSystem.cpp
//  Breathless
//
//  Created by Paul on 28/7/19.
//  Copyright © 2019 syn. All rights reserved.
//

float m_flOldCurtime;
float m_flOldFrametime;

void StartPrediction(CUserCmd* cmd)
{
    if (!vars.aimbot.prediction)
        return;
    
    C_BasePlayer* localplayer = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    *nPredictionRandomSeed = MD5_PseudoRandom(cmd->command_number) & 0x7FFFFFFF;
    
    m_flOldCurtime = pGlobals->curtime;
    m_flOldFrametime = pGlobals->frametime;
    
    pGlobals->curtime = localplayer->GetTickBase() * pGlobals->interval_per_tick;
    pGlobals->frametime = pGlobals->interval_per_tick;
    
    pGameMovement->StartTrackPredictionErrors(localplayer);
    
    pMoveHelper->SetHost(localplayer);
    pPrediction->SetupMove(localplayer, cmd, pMoveHelper, MoveData);
    pGameMovement->ProcessMovement(localplayer, MoveData);
    pPrediction->FinishMove(localplayer, cmd, MoveData);
}

void EndPrediction()
{
    if (!vars.aimbot.prediction)
        return;
    
    C_BasePlayer* localplayer = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    pGameMovement->FinishTrackPredictionErrors(localplayer);
    pMoveHelper->SetHost(0);
    
    *nPredictionRandomSeed = -1;
    
    pGlobals->curtime = m_flOldCurtime;
    pGlobals->frametime = m_flOldFrametime;
}
