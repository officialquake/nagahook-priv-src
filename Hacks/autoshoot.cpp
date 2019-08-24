//
//  autoshoot.cpp
//  pwned
//
#include "autoshoot.h"

/*void AutoShoot(C_BaseEntity* player, C_BaseCombatWeapon* activeWeapon, CUserCmd* cmd)*/


float Hitchance(C_BaseEntity* pLocal, C_BaseCombatWeapon* pWeapon)
{
    float hitchance = 101;
    if (!pWeapon) return 0;
    if(vars.aimbot.accuracyhithcance > 1)
    {
        float inaccuracy = pWeapon->GetInaccuracy();
        if (inaccuracy == 0) inaccuracy = 0.0000001;
        inaccuracy = 1 / inaccuracy;
        hitchance = inaccuracy;
    }
    return hitchance;
}

void AutoShoot(C_BaseEntity* player, C_BaseCombatWeapon* activeWeapon, CUserCmd* cmd)
{
    if (!vars.aimbot.autoshoot)
        return;
    
    if (!player || !activeWeapon || activeWeapon->GetAmmo() == 0)
        return;
    
    CSWeaponType weaponType = (CSWeaponType)activeWeapon->GetCSWpnData()->m_WeaponType;
    
    if (weaponType == CSWeaponType::WEAPONTYPE_KNIFE || weaponType == CSWeaponType::WEAPONTYPE_C4 || weaponType == CSWeaponType::WEAPONTYPE_GRENADE)
        return;
    
    
    if (cmd->buttons & IN_USE)
        return;
    
    if (cmd->buttons & IN_ATTACK) {
        cmd->viewangles.y;
    }
    
    float nextPrimaryAttack = activeWeapon->GetNextPrimaryAttack();
    float server_time = player->GetTickBase() * pGlobals->interval_per_tick;
    
    
    
    
    if ((vars.aimbot.accuracyhithcance * 1.5 <= Hitchance(player, activeWeapon)) || vars.aimbot.accuracyhithcance == 0 || *activeWeapon->GetItemDefinitionIndex() == ItemDefinitionIndex::WEAPON_REVOLVER)
    {
        if (vars.aimbot.silent)
        {
            if (vars.aimbot.autoshoot && !(cmd->buttons & IN_ATTACK))
                
            {
                cmd->buttons |= IN_ATTACK;
            }
            else
            {
                return;
            }
        }
        else if (vars.aimbot.autoshoot)
        {
            if (nextPrimaryAttack > server_time){
                if (*activeWeapon->GetItemDefinitionIndex() == ItemDefinitionIndex::WEAPON_REVOLVER){
                    cmd->buttons &= ~IN_ATTACK2;
                }else{
                    cmd->buttons &= ~IN_ATTACK;
                }
            }
        }
    }
    
}


void AutoCock(CUserCmd* pCmd, C_BaseCombatWeapon* weapon)
{
    if(!vars.aimbot.autoshoot)
        return;
    
    //bool shootingRevolver = false;
    
    if ( pCmd->buttons & IN_RELOAD )
        return;
    
    if ( *weapon->GetItemDefinitionIndex() != ItemDefinitionIndex::WEAPON_REVOLVER )
        return;
    static int timer = 0;
    timer++;
    
    if ( timer <= 15 )
        pCmd->buttons |= IN_ATTACK;
    
    else
        timer = 0;
}


void ContinuousPistols(CUserCmd* pCmd, C_BaseCombatWeapon* weapon)
{
    if(!vars.aimbot.autopistol)
        return;
    
    if(!weapon->IsPistol())
        return;
    
    if (pCmd->buttons & IN_ATTACK)
    {
        static bool bAttack = false;
        
        if (bAttack)
            pCmd->buttons |= IN_ATTACK;
        else
            pCmd->buttons &= ~IN_ATTACK;
        
        bAttack = !bAttack;
    }
    
}

void AutoKnife(CUserCmd* cmd){
    if (!vars.aimbot.autoknife) {
        return;
    }
    
    C_BaseEntity* LocalPlayer = pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    if (!LocalPlayer || !LocalPlayer->IsPlayer()) {
        return;
    }
    
    C_BaseCombatWeapon* activeWeapon = (C_BaseCombatWeapon*)pEntList->GetClientEntityFromHandle(LocalPlayer->GetActiveWeapon());
    if (!activeWeapon) {
        return;
    }
    
    if ((CSWeaponType)activeWeapon->GetCSWpnData()->m_WeaponType != CSWeaponType::WEAPONTYPE_KNIFE)
        return;
    
    Vector traceStart, traceEnd;
    trace_t tr;
    
    Vector angles;
    pEngine->GetViewAngles(angles);
    Vector viewAnglesRcs = angles + LocalPlayer->GetPunchAngles() * 2.0f;
    
    AngleVectors(viewAnglesRcs, &traceEnd);
    
    traceStart = LocalPlayer->GetEyePosition();
    traceEnd = traceStart + (traceEnd * 8192.0f);
    
    Ray_t ray;
    ray.Init(traceStart, traceEnd);
    CTraceFilter traceFilter;
    traceFilter.pSkip = LocalPlayer;
    pEngineTrace->TraceRay(ray, 0x46004003, &traceFilter, &tr);
    
    C_BaseEntity* player = pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    if (!player) {
        return;
    }
    
    if (player->GetClientClass()->m_ClassID != EClassIds::CCSPlayer) {
        return;
    }
    
    if (player == LocalPlayer || player->GetDormant() || !player->GetAlive() || player->GetImmune()) {
        return;
    }
    
    if (player->GetTeam() == LocalPlayer->GetTeam()) {
        return;
    }
    
    Vector localPlayerOrigin = LocalPlayer->GetVecOrigin();
    float playerDistance = localPlayerOrigin.DistTo(player->GetVecOrigin());
    if (activeWeapon->GetNextPrimaryAttack() < pGlobals->curtime){
        if (playerDistance <= 65.f && GetRightKnifeDamageDone(LocalPlayer, player) >= player->GetHealth()) {
            cmd->buttons |= IN_ATTACK2;
        } else if (IsPlayerBehind(LocalPlayer, player) && playerDistance <= 65.f) {
            cmd->buttons |= IN_ATTACK2;
        } else if (playerDistance <= 78.f) {
            if (IsPlayerBehind(LocalPlayer, player)) {
                return;
            }
            
            if (playerDistance <= 65.f &&
                (2 * GetLeftKnifeDamageDone(LocalPlayer, player)) + (GetRightKnifeDamageDone(LocalPlayer, player) - 13) < player->GetHealth()
                ) {
                cmd->buttons |= IN_ATTACK2;
            } else {
                cmd->buttons |= IN_ATTACK;
            }
        }
    }
}

bool IsPlayerBehind(C_BaseEntity* localplayer, C_BaseEntity* player) {
    Vector toTarget = (localplayer->GetVecOrigin() - player->GetVecOrigin());
    Vector playerViewAngles;
    AngleVectors(player->GetEyePosition(), &playerViewAngles);
    if (toTarget.Normalized().Dot(playerViewAngles) > -0.5f) {
        return false;
    } else {
        return true;
    }
}

int GetLeftKnifeDamageDone(C_BaseEntity* localplayer, C_BaseEntity* player) {
    bool backstab = IsPlayerBehind(localplayer, player);
    int armor = player->GetArmor();
    if (!backstab) {
        if (armor > 0) {
            return 33; // 21
        } else {
            return 39; // 25
        }
    } else {
        if (armor > 0) {
            return 76; // 76
        } else {
            return 90; // 90
        }
    }
}

int GetRightKnifeDamageDone(C_BaseEntity* localplayer, C_BaseEntity* player) {
    bool backstab = IsPlayerBehind(localplayer, player);
    int armor = player->GetArmor();
    if (!backstab) {
        if (armor > 0) {
            return 33; // 21
        } else {
            return 39; // 25
        }
    } else {
        return 100;
    }
}

void AutoZeus(CUserCmd* cmd, C_BaseEntity* pLocal, C_BaseCombatWeapon* weapon) {
    
    if (!vars.aimbot.autoshoot)
        return;
    
    if (!pLocal || !pLocal->GetAlive())
        return;
    
    if (!weapon)
        return;
    
    if (!WEAPON_TASER)
        return;
    
    if (weapon->GetAmmo() == 0)
        return;
    
    for (int i = 1; i <= pGlobals->maxClients; i++)
    {
        C_BaseEntity *entity = (C_BaseEntity*)pEntList->GetClientEntity(i);
        if (!entity
            || entity == pLocal
            || entity->GetDormant()
            || entity->GetLifeState() != LIFE_ALIVE
            || entity->GetImmune()
            || entity->GetClientClass()->m_ClassID != (int)CCSPlayer
            || entity->GetTeam() == pLocal->GetTeam()
            || !(entity->GetFlags() & FL_ONGROUND))
            continue;
        
        Vector traceStart, traceEnd;
        
        Vector viewAngles;
        pEngine->GetViewAngles(viewAngles);
        Vector viewAnglesRcs = viewAngles + (pLocal->GetPunchAngles() * 2.0f);
        
        AngleVectors(viewAnglesRcs, &traceEnd);
        
        traceStart = pLocal->GetEyePosition();
        traceEnd = traceStart + (traceEnd * 8192.0f);
        
        Ray_t ray;
        trace_t Trace;
        ray.Init(traceStart, traceEnd);
        CTraceFilter traceFilter;
        traceFilter.pSkip = pLocal;
        pEngineTrace->TraceRay(ray, 0x46004003, &traceFilter, &Trace);
        
        if (!Trace.m_pEnt)
            return;
        if (!Trace.m_pEnt->GetAlive())
            return;
        if (Trace.m_pEnt->GetImmune())
            return;
        
        if (pLocal->GetTeam() == Trace.m_pEnt->GetTeam())
            return;
        
        float playerDistance = pLocal->GetVecOrigin().DistTo ( pLocal->GetVecOrigin() );
        if ( weapon->GetNextPrimaryAttack() < pGlobals->curtime ) {
            if (*weapon->GetItemDefinitionIndex() == ItemDefinitionIndex::WEAPON_TASER ) {
                if ( playerDistance <= 184.f )
                    cmd->buttons |= IN_ATTACK;
            }
        }
    }
}
