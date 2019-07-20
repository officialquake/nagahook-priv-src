#include "main.h"
#include "noduckcooldown.hpp"



CDuck* duck = new CDuck();

void CDuck::DuckCool(CUserCmd* cmd)
{
    if (!vars.misc.noduckcooldown)
        return;
    
    C_BasePlayer* localplayer = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    if (!localplayer || !localplayer->GetAlive())
        return;
    
    cmd->buttons |= IN_BULLRUSH;
}
