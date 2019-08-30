#include "main.h"
#include "skinchanger.h"
#include "asuswalls.h"
#include "LagComp.h"
#include "../Backtrack.hpp"
#include "../Hacks/nosmoke.hpp"
#include "../Hacks/antiaim.h"
#include "../Hacks/resolver.h"

#include "../Hacks/namestealer.hpp"

float GetMaxxDelta(CCSGOAnimState *animState ) {
    
    float speedFraction = std::max(0.0f, std::min(animState->feetShuffleSpeed, 1.0f));
    
    float speedFactor = std::max(0.0f, std::min(1.0f, animState->feetShuffleSpeed2));
    
    float unk1 = ((animState->runningAccelProgress * -0.30000001) - 0.19999999) * speedFraction;
    float unk2 = unk1 + 1.0f;
    float delta;
    
    if (animState->duckProgress > 0)
    {
        unk2 += ((animState->duckProgress * speedFactor) * (0.5f - unk2));// - 1.f
    }
    
    delta = *(float*)((uintptr_t)animState + 0x3A4) * unk2;
    
    return abs(delta);
}

void RemoveFlash(ClientFrameStage_t stage)
{
    if (!pEngine->IsInGame())
        return;
    
    if(!vars.misc.noflash)
        return;
    
    if (stage != ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START)
        return;
    
    C_BaseEntity* localplayer = (C_BaseEntity*)pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    if (!localplayer)
        return;
    
    if (vars.misc.noflash)
    {
        *localplayer->GetFlashMaxAlpha() = 255.0f - vars.misc.flashalpha;
    }
    else
    {
        *localplayer->GetFlashMaxAlpha() = 255.0f;
    }
    
}
void FakePing()
{
    if(!vars.misc.fakeping)
        return;
    
    static auto net_fakelag = pCvar->FindVar("net_fakelag"); // nasa shit
    if (vars.misc.fakepingtype == 1)
        net_fakelag->SetValue(vars.misc.fakepingvalue);
    else if (vars.misc.fakepingtype == 2)
    {
        if (pInputSystem->IsButtonDown(KEY_P))
            net_fakelag->SetValue(vars.misc.fakepingvalue);
        else net_fakelag->SetValue(0);
    }
    else
    {
        net_fakelag->SetValue(0);
    }
}

void hkFrameStage(void* thisptr, ClientFrameStage_t curStage)
{
    auto* local = pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    if(!local)
        return;
    
    Vector* PointerPunch    = nullptr;
    Vector* PointerView     = nullptr;
    
    Vector VecPunch, VecView;
    
    /*if(vars.misc.thirdpersonmode)
     {
     if (curStage == ClientFrameStage_t::FRAME_RENDER_START && (pEngine->IsConnected() && pEngine->IsInGame()))
     {
     
     
     }
     
     }*/
    
    if(curStage == ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START)
    {
        if(vars.aimbot.backtrack)
        {
            for(int i = 0; i < 64; i++ )
            {
                auto entity = (C_BaseEntity*)pEntList->GetClientEntity(i);
                
                if(!entity)
                    continue;
                
                if(entity == local)
                    continue;
                
                if(entity->GetDormant())
                    continue;
                
                if(entity->IsGhost())
                    continue;
                
                if(entity->GetImmune())
                    continue;
                
                //if(entity->GetTeam() == Global::local->GetTeam())
                //continue;
                
                if(!entity->GetAlive())
                    continue;
                
                backtracking->Update(pGlobals->tickcount);
            }
        }
    }
    
    if(vars.visuals.skinc) {
        skinchanger->FrameStageNotify(curStage);
    }
    if(vars.misc.updateskins) {
        skinchanger->ForceSkins();
    }
    
    
    if(vars.misc.asuswalls)
        asuswalls(curStage);
    
    if(curStage == FRAME_NET_UPDATE_POSTDATAUPDATE_END)
    {
        smoke->remove_smoke(curStage);
    }
    
    
    
    if(vars.misc.thirdpersonmode) {
        if (curStage == ClientFrameStage_t::FRAME_RENDER_START && (pEngine->IsConnected() && pEngine->IsInGame())) {
        }
    }
    
    if(curStage == FRAME_RENDER_START && local) {
        if(vars.misc.thirdpersonmode) {
            if(pEngine->IsConnected() && pEngine->IsInGame()) {
                if(local->GetLifeState() == LIFE_ALIVE) {
                    *reinterpret_cast<Vector*>(reinterpret_cast<uintptr_t>(local) + offsets.DT_BasePlayer.deadflag + 0x4) = tpangles;
                }
            }
        }
        
        
        
        
        if(vars.misc.novisual)
        {
            if(local->GetLifeState() == LIFE_ALIVE)
            {
                PointerPunch = (Vector*)((uintptr_t)local + offsets.DT_BasePlayer.m_aimPunchAngle);
                PointerView = (Vector*)((uintptr_t)local + offsets.DT_BasePlayer.m_viewPunchAngle);
                
                VecPunch = *PointerPunch;
                VecView = *PointerView;
                
                PointerPunch->Init();
                PointerView->Init();
            }
            
        }
        
    }
    
    
    {   // Call functions here just so its cleaner
        RemoveFlash(curStage);
        //FakePing();
        ViewmodelHVH();
        InverseRagdoll();
        Resolver::FrameStageNotify(curStage, local);
    
        //Resolver1::FrameStageNotify1(curStage, local);
        
        
        
        
        
    }
    
    clientVMT->GetOriginalMethod<tFrameStage>(37)(thisptr, curStage);
    
    Resolver::PostFrameStageNotify(curStage);
    //Resolver1::PostFrameStageNotify1(curStage);
    
    if(pEngine->IsInGame() && vars.aimbot.enabled && vars.aimbot.Yawresolver && curStage == ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START && vars.aimbot.yresolve > 0)
    {
        if(vars.aimbot.backtrack)
        {
            for(int i = 1; i < pEngine->GetMaxClients(); i++)
            {
                auto* entity = pEntList->GetClientEntity(i);
                
                if(!entity)
                    continue;
                
                if(!entity->GetAlive())
                    continue;
                
                if(entity->GetImmune())
                    continue;
                
                if(entity->GetDormant())
                    continue;
                
                if(entity == local)
                    continue;
                
                if(!gCorrections[entity->GetIndex()].resolved)
                    continue;
                
                backtracking->Update(pGlobals->tickcount);
                
                //*(float*)((uintptr_t)entity + offsets.DT_BasePlayer.m_angRotation1) = AAA_Pitch(entity);
                *(float*)((uintptr_t)entity + offsets.DT_BasePlayer.m_angRotation2) = AAA_Yaw(entity);
            }
        }
        
    }
    
    if(PointerPunch && PointerView)
    {
        *PointerPunch   = VecPunch;
        *PointerView    = VecView;
    }
    

    
}
