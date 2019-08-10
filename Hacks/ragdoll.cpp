//
//  ragdoll.cpp
//  vHook
//
//  Created by Timothy Dillan on 9/8/19.
//  Copyright © 2019 ViKiNG. All rights reserved.
//

#include "ragdoll.hpp"
CRagdoll* doll = new CRagdoll();
void CRagdoll::inverseRagDoll(C_BaseEntity* ent)
{
    if(!vars.visuals.inverseragdoll)
        return;
    
    
    auto weapon = GetActiveWeapon(ent);
    
    
    if (*weapon->GetItemDefinitionIndex() == ItemDefinitionIndex::WEAPON_KNIFE )
    {
        pEngine->ExecuteClientCmd("cl_righthand 0");
    }else{
        pEngine->ExecuteClientCmd("cl_righthand 1");
    }
}
