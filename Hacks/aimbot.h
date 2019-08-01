//
//  aimbot.hpp
//  vHook
//
#pragma once

#include "main.h"

void DoAim(CUserCmd* pCmd, C_BaseEntity* local, C_BaseCombatWeapon* weapon, float& flForward, float& flSide);
//void AutoSlow(C_BasePlayer* player, float& forward, float& sideMove, float& bestDamage, C_BaseCombatWeapon* active_weapon, CUserCmd* cmd);
//void velocityhitchance(C_BaseEntity* local, C_BaseCombatWeapon* weapon);


namespace Aimbot
{
    extern C_BaseEntity* curTarget;
}


enum HITSCAN
{
    low     = 1,
    normal          = 2,
    high      = 3,
    extreme        = 4,
    baim          = 5,
    //test2       = 6,
    //Mixed       = 7,
};

