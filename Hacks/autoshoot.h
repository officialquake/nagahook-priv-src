//
//  autoshoot.hpp
//  pwned
//

#include "../main.h"

void AutoShoot(C_BaseEntity* player, C_BaseCombatWeapon* activeWeapon, CUserCmd* cmd);

void ContinuousPistols(CUserCmd* pCmd, C_BaseCombatWeapon* weapon);

float Hitchance(C_BaseEntity* pLocal, C_BaseCombatWeapon* pWeapon);

void AutoCock(CUserCmd* pCmd, C_BaseCombatWeapon* weapon);

void AutoKnife(C_BaseEntity* playerknife, CUserCmd* cmd);

bool IsPlayerBehind(C_BaseEntity* localplayer, C_BaseEntity* player);
int GetLeftKnifeDamageDone(C_BaseEntity* localplayer, C_BaseEntity* player);
int GetRightKnifeDamageDone(C_BaseEntity* localplayer, C_BaseEntity* player);


