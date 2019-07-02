#include "triggerbot.hpp"
void DoTrigger(CUserCmd *Cmd)
{
    if(!vars.aimbot.trigger)
        return;
    
    if(pInputSystem->IsButtonDown(KEY_COMMA)) // Change the trigger bot key here
    {
        C_BaseEntity* LocalPlayer = (C_BaseEntity*)pEntList->GetClientEntity(pEngine->GetLocalPlayer());
        
        if (!LocalPlayer || LocalPlayer->GetHealth() < 0)
            return;
        
        
        C_BaseCombatWeapon* activeWeapon = GetActiveWeapon(LocalPlayer);
        
        if (!activeWeapon || activeWeapon->GetAmmo() == 0)
            return;
        
        
        Vector traceStart, traceEnd;
        
        Vector viewAngles;
        pEngine->GetViewAngles(viewAngles);
        Vector viewAngles_rcs = viewAngles + (LocalPlayer->GetPunchAngles() * 2.0f);
        
        AngleVectors(viewAngles_rcs, &traceEnd);
        
        traceStart = LocalPlayer->GetEyePosition();
        traceEnd = traceStart + (traceEnd * 8192.0f);
        
        Ray_t ray;
        trace_t trace;
        CTraceFilter filter;
        filter.pSkip = LocalPlayer;
        
        ray.Init(traceStart, traceEnd);
        pEngineTrace->TraceRay(ray, MASK_SHOT, &filter, &trace);
        
        if (trace.allsolid || trace.startsolid)
            return;
        
        
        C_BaseEntity* player = (C_BaseEntity*)trace.m_pEnt;
        
        if(!player || player->GetHealth() < 0 || player->GetImmune())
            return;
        
        
        if(player->GetClientClass()->m_ClassID != EClassIds::CCSPlayer)
            return;
        
        
        if(LocalPlayer->GetTeam() == player->GetTeam())
            return;
        
        
        if (activeWeapon->GetNextPrimaryAttack() > pGlobals->curtime)
        {
            if (*activeWeapon->GetItemDefinitionIndex() == WEAPON_REVOLVER)
            {
                Cmd->buttons &= ~IN_ATTACK2;
            }
            else
            {
                Cmd->buttons &= ~IN_ATTACK;
            }
        }
        else
        {
            if (*activeWeapon->GetItemDefinitionIndex() == WEAPON_REVOLVER)
            {
                Cmd->buttons |= IN_ATTACK2;
            }
            else
            {
                Cmd->buttons |= IN_ATTACK;
            }
            
        }
        
    }
    
}

