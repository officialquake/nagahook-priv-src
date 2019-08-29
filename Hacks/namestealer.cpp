//
//  namestealer.cpp
//  vHook
//
//  Created by Timothy Dillan on 28/8/19.
//  Copyright © 2019 ViKiNG. All rights reserved.
//

#include "namestealer.hpp"

int NameStealer::changes = -1;
void NameStealer::SetName(const char* name)
{
    ConVar* cvar_name = pCvar->FindVar("name");
    cvar_name->fnChangeCallback = 0;
    cvar_name->SetValue(name);
}


void NameStealer::BeginFrame(float frameTime)
{
    if (!pEngine->IsInGame())
        return;
    
    if (changes == -1)
        return;
    
    long currentTime_ms = GetEpochTime();
    static long timeStamp = currentTime_ms;
    
    if (currentTime_ms - timeStamp < 150)
        return;
    
    timeStamp = currentTime_ms;
    changes++;
    
    if (changes >= 5)
    {
        if(vars.aimbot.namestealer){
            if(vars.aimbot.nametype == 0){
                SetName("𝖋𝖚𝖈𝕶 𝖇𝖔𝖞 𝕴𝖓𝖈");
            }else if(vars.aimbot.nametype == 1){
                SetName("unnamed");
            }else if(vars.aimbot.nametype == 2){
                SetName(":(");
            }else if(vars.aimbot.nametype == 3){
                SetName("?");
            }else if(vars.aimbot.nametype == 4){
                SetName("not hittin p");
            }
        }
        
        changes = -1;
        
        return;
    }
    
    SetName("realnigga.club");
}
