//
//  ragdoll.cpp
//  vHook
//
//  Created by Timothy Dillan on 9/8/19.
//  Copyright © 2019 ViKiNG. All rights reserved.
//

#include "ragdoll.hpp"
CRagdoll* doll = new CRagdoll();
void CRagdoll::inverseRagDoll()
{
    if(!vars.visuals.inverseragdoll)
        return;
    
    C_BasePlayer* localPlayer = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    C_BaseCombatWeapon *activeWeapon = (C_BaseCombatWeapon*)pEntList->GetClientEntityFromHandle(localPlayer->GetActiveWeapon());
    
    if (!activeWeapon || (CSWeaponType)activeWeapon->GetCSWpnData()->m_WeaponType != CSWeaponType::WEAPONTYPE_KNIFE)
        return;
    
    pEngine->ExecuteClientCmd("cl_righthand 0");
}
