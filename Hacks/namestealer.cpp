//
//  namestealer.cpp
//  vHook
//
//  Created by Timothy Dillan on 28/8/19.
//  Copyright © 2019 ViKiNG. All rights reserved.
//

#include "namestealer.hpp"

void NameStealer::SetName(const char* name)
{
    ConVar* cvar_name = pCvar->FindVar("name");
    cvar_name->fnChangeCallback = 0;
    cvar_name->SetValue(name);
}
