//
//  visuals.cpp
//  vHook
//
//  Created by Timothy Dillan on 6/30/19.
//  Copyright © 2019 ViKiNG. All rights reserved.
//

#include "visuals.hpp"
C_Visuals* visuals = new C_Visuals();
void C_Visuals::draw_player_esp(C_BasePlayer* player)
{
    
    if(!player->GetAlive())
        return;
    
    if(player->GetDormant())
        return;
    
    int  team = player->GetTeam();
    bool visible = is_player_visible(player);
    
    if(vars.visuals.visonly && !visible)
        return;
    
    if(vars.visuals.enemyonly && team == Global::local->GetTeam())
        return;
    
    if(vars.misc.radar)
        *player->GetSpotted() = true;
}

void C_Visuals::draw_esp()
{
    if(!vars.visuals.enabled)
        return;
    
    if(!Global::local)
        return;
    
    for(int i = 0; i < pEntList->GetHighestEntityIndex(); i++)
    {
        C_BaseEntity* entity = pEntList->GetClientEntity(i);
        
        if(!entity)
            continue;
        
        if(entity->IsPlayer())
            this->draw_player_esp((C_BasePlayer*)entity);
    }
}
