#include "hitmarker.h"
#include "../Utils/utils.h"
#include "../Hacks/hacks.h"

void Hitmarkers::FireGameEvent(IGameEvent* event) {
    
    if(!pEngine->IsInGame())
        return;
    if(!vars.visuals.hitmarker)
        return;
    
    if(strcmp(event->GetName(), "player_hurt") != 0)
        return;
    int hurt_player_id = event->GetInt("userid");
    int attacker_id = event->GetInt("attacker");
    
    if(pEngine->GetPlayerForUserID(hurt_player_id) == pEngine->GetLocalPlayer())
        return;
    
    if(hurt_player_id != pEngine->GetLocalPlayer() && attacker_id == pEngine->GetLocalPlayer())
    {
        pCvar->ConsoleColorPrintf(Color::Green(), "Player hurt.");
        pSurface->PlaySound("skeet.wav");
    }
    
}
