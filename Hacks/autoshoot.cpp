//
//  autoshoot.cpp
//  pwned
//
#include "autoshoot.h"

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
    
    float nextPrimaryAttack = activeWeapon->GetNextPrimaryAttack();
    float server_time = player->GetTickBase() * pGlobals->interval_per_tick;
    
    if (nextPrimaryAttack > server_time)
    {
        if (*activeWeapon->GetItemDefinitionIndex() == ItemDefinitionIndex::WEAPON_REVOLVER)
            cmd->buttons &= ~IN_ATTACK2;
        else
            cmd->buttons &= ~IN_ATTACK;
    }
    else
    {
        if (*activeWeapon->GetItemDefinitionIndex() == ItemDefinitionIndex::WEAPON_REVOLVER)
            cmd->buttons |= IN_ATTACK2;
        else
            cmd->buttons |= IN_ATTACK;
    }
    
    if (*activeWeapon->GetItemDefinitionIndex() == ItemDefinitionIndex::WEAPON_TASER ) {
        float playerDistance = player->GetVecOrigin().DistTo ( player->GetVecOrigin() );
        
        Vector zeus_point;
        zeus_point = GetHitboxPosition(player, (int)HITBOX_BELLY);
        if ( playerDistance <= 184.f )
        {
            //cmd->buttons &= ~IN_ATTACK;
            cmd->buttons |= IN_ATTACK;
        }
    }
    
    
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
// Auto Revolver
void AutoCock(CUserCmd* pCmd, C_BaseCombatWeapon* weapon)
{
    if(!vars.aimbot.autocock && !vars.aimbot.autoshoot)
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
