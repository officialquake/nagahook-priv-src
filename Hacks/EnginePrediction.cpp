#include "EnginePrediction.h"
#include "../Utils/checksum_md5.h"

CEnginePrediction* CEnginePrediction::instance = nullptr;

CEnginePrediction::CEnginePrediction() {}

void CEnginePrediction::StartSingle(CUserCmd* cmd, C_BaseCombatWeapon* pWeapon, C_BaseEntity* pLocal) {
    
    if (!pMoveHelper)
        return;

    
    float backup = pGlobals->frametime;
    int oldFlags = pLocal->GetFlags();
    
    pGlobals->frametime = pGlobals->interval_per_tick;
    
    pWeapon->UpdateAccuracyPenalty();
    
    pPrediction->SetupMove(pLocal, cmd, pMoveHelper, MoveData);
    pGameMovement->ProcessMovement(pLocal, MoveData);
    pPrediction->FinishMove(pLocal, cmd, MoveData);
    
    pGlobals->frametime = backup;
    *pLocal->pGetFlags() = oldFlags;
}

void CEnginePrediction::Start(CUserCmd* cmd) {
    
    if (!pMoveHelper)
        return;
    
    C_BaseEntity* LocalPlayer = (C_BaseEntity*)pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    if (!LocalPlayer)
        return;

    
    *nPredictionRandomSeed = MD5_PseudoRandom(cmd->command_number) & 0x7FFFFFFF;
    
    oldPFlags = LocalPlayer->GetFlags();
    
    m_flOldCurtime = pGlobals->curtime;
    m_flOldFrametime = pGlobals->frametime;
    
    pGlobals->curtime = LocalPlayer->GetTickBase() * pGlobals->interval_per_tick;
    pGlobals->frametime = pGlobals->interval_per_tick;
    
    pGameMovement->StartTrackPredictionErrors(LocalPlayer);
    
    pMoveHelper->SetHost(LocalPlayer);
    pPrediction->SetupMove(LocalPlayer, cmd, pMoveHelper, MoveData);
    pGameMovement->ProcessMovement(LocalPlayer, MoveData);
    pPrediction->FinishMove(LocalPlayer, cmd, MoveData);
}

void CEnginePrediction::End() {
    
    if (!pMoveHelper)
        return;
    
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
