//
//  ragdoll.cpp
//  vHook
//
//  Created by Timothy Dillan on 9/8/19.
//  Copyright © 2019 ViKiNG. All rights reserved.
//

#include "ragdoll.hpp"
CRagdoll* doll = new CRagdoll();
void CRagdoll::inverseRagDol(CUserCmd* cmd, C_BaseEntity* local,  C_BaseCombatWeapon* weapon)
{
    if(!vars.visuals.inverseragdoll)
        return;
    
    if(!pEngine->IsInGame())
        return;
    if(!local->GetAlive())
        return;
    C_BaseCombatWeapon* activeWeapon = (C_BaseCombatWeapon*)pEntList->GetClientEntityFromHandle(local->GetActiveWeapon());
    if (!activeWeapon)
        return;
    
    if ((CSWeaponType)activeWeapon->GetCSWpnData()->m_WeaponType == CSWeaponType::WEAPONTYPE_KNIFE){
        pEngine->ClientCmd_Unrestricted("cl_righthand 0");
    }else{
        pEngine->ClientCmd_Unrestricted("cl_righthand 1");
    }
}
