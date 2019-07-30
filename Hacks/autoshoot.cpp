//
//  autoshoot.cpp
//  pwned
//
#include "autoshoot.h"

/*void AutoShoot(C_BaseEntity* player, C_BaseCombatWeapon* activeWeapon, CUserCmd* cmd)*/


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
    
    C_BasePlayer* localplayer = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    if (vars.aimbot.autoscope &&  activeWeapon->IsSnipScope() && activeWeapon->GetCSWpnData()->m_iZoomLevels > 0 && !localplayer->IsScoped())
        cmd->buttons |= IN_ATTACK2;

    
    float nextPrimaryAttack = activeWeapon->GetNextPrimaryAttack();
    
    if (!(*activeWeapon->GetItemDefinitionIndex() == ItemDefinitionIndex::WEAPON_REVOLVER))
    {
        if (nextPrimaryAttack > pGlobals->curtime)
            cmd->buttons &= ~IN_ATTACK;
        else
            cmd->buttons |= IN_ATTACK;
    }
}



void ContinuousPistols(CUserCmd* pCmd, C_BaseCombatWeapon* weapon)
{
    if (!vars.aimbot.autopistol || !vars.aimbot.autoshoot)
        return;
    
    CSWeaponType weaponType = (CSWeaponType)weapon->GetCSWpnData()->m_WeaponType;
    
    if (!weapon || weaponType != CSWeaponType::WEAPONTYPE_PISTOL)
        return;
    
    if (weapon->GetNextPrimaryAttack() < pGlobals->curtime)
        return;
    
    if (*weapon->GetItemDefinitionIndex() != ItemDefinitionIndex::WEAPON_REVOLVER)
        pCmd->buttons &= ~IN_ATTACK;
    
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
