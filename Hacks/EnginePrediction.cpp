#include "EnginePrediction.h"
#include "../Utils/checksum_md5.h"


CEnginePrediction::CEnginePrediction() {}

void CEnginePrediction::Start(CUserCmd* cmd) {
    m_flOldCurtime = pGlobals->curtime;
    m_flOldFrametime = pGlobals->frametime;
    
    
    C_BaseEntity* LocalPlayer = (C_BaseEntity*)pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    if (!LocalPlayer)
        return;

    pMoveHelper->SetHost(LocalPlayer);
    
    *nPredictionRandomSeed = MD5_PseudoRandom(cmd->command_number) & 0x7FFFFFFF;
    
    oldPFlags = LocalPlayer->GetFlags();
    pGlobals->curtime = LocalPlayer->GetTickBase() * pGlobals->interval_per_tick;
    pGlobals->frametime = pGlobals->interval_per_tick;
    pGameMovement->StartTrackPredictionErrors(LocalPlayer);
    memset(&m_MoveData, 0, sizeof(m_MoveData));
    pPrediction->SetupMove(LocalPlayer, cmd, pMoveHelper, MoveData);
    pGameMovement->ProcessMovement(LocalPlayer, MoveData);
    pPrediction->FinishMove(LocalPlayer, cmd, MoveData);
}

void CEnginePrediction::End() {

    
    C_BaseEntity* LocalPlayer = (C_BaseEntity*)pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    if (!LocalPlayer)
        return;
    
    pGameMovement->FinishTrackPredictionErrors(LocalPlayer);
    pMoveHelper->SetHost(0);
    
    *nPredictionRandomSeed = -1;
    *LocalPlayer->pGetFlags() = oldPFlags;
    
    pGlobals->curtime = m_flOldCurtime;
    pGlobals->frametime = m_flOldFrametime;
}
