#include "hitmarker.h"

std::vector<std::pair<int, long>> damages;
long lastHitmarkerTimestamp = 0;

//CHitmarkers* hitmarker = new CHitmarkers();

void Hitmarkers::Paint(){
    
    if(!pEngine->IsInGame())
        return;
    if(!vars.visuals.hitmarker)
        return;
    C_BasePlayer* localplayer = (C_BasePlayer*)pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    if(!localplayer)
        return;
    
    if(!localplayer->GetAlive())
        return;
    
    int duration = 2000;
    long now = GetEpochTime();
    
    long diff = lastHitmarkerTimestamp + duration - now;
    if(diff <= 0)
        return;
    
    int w, h;
    pEngine->GetScreenSize(w, h);
    
    Color color = Color::Red();
    float sc = 1.0f/255.0f;
    color.SetAlpha(min(color.a(), (int)(diff * (color.a() / sc) / duration * 2)) * sc);
    int sides[4][2] = { {-1, -1}, {1, 1}, {-1, 1}, {1, -1} };
    for (auto& it : sides)
        draw->drawline(w / 2 +  (vars.visuals.hitinnergap * it[0]), h / 2 + (vars.visuals.hitinnergap * it[1]), w / 2 + (vars.visuals.hitsize * it[0]), h / 2 + (vars.visuals.hitsize * it[1]), color);
    float textHeight = draw->GetTextSize("[cool]", eFont).y;
    for (unsigned int i = 0; i < damages.size(); i++) {
        long timestamp = damages[i].second;
        long hitDiff = timestamp + duration - now;
        
        if(hitDiff <= 0) {
            damages.erase(damages.begin() + i);
            continue;
        }
        Vector2D pos = Vector2D(w / 2 + vars.visuals.hitsize + 4, h / 2 - vars.visuals.hitsize - textHeight * i + 4);
        
        int damage = damages[i].first;
        std::string damageStr = '-' + std::to_string(damage);
        color.SetAlpha(min(color.a(), (int)(hitDiff * (color.a() / sc) / duration * 2)) * sc);
        
        draw->drawstring(pos, damageStr.c_str(), eFont, color);
        //draw->AddText(w / 2 + vars.visuals.hitsize + 4, h / 2 - vars.visuals.hitsize - textHeight * i + 4, damageStr.c_str(), color);
    }
}

void Hitmarkers::FireGameEvent(IGameEvent* event)
{    
    if(!pEngine->IsInGame())
        return;
    
    if(!vars.visuals.hitmarker)
        return;
    
    
    if (strcmp(event->GetName(), "player_hurt") != 0)
        return;
    
    int hurt_player_id = event->GetInt("userid");
    int attacker_id = event->GetInt("attacker");
    
    if(pEngine->GetPlayerForUserID(hurt_player_id) == pEngine->GetLocalPlayer())
        return;
    
    if(pEngine->GetPlayerForUserID(attacker_id) != pEngine->GetLocalPlayer())
        return;
    
    C_BasePlayer* localplayer = (C_BasePlayer*)pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    if(!localplayer)
        return;
    C_BasePlayer* hurt_player = (C_BasePlayer*)pEntList->GetClientEntity(pEngine->GetPlayerForUserID(hurt_player_id));
    if(!hurt_player)
        return;
    if (hurt_player->GetTeam() == localplayer->GetTeam() && !vars.visuals.allieshit)
        return;
    
    if (hurt_player->GetTeam() != localplayer->GetTeam() && !vars.visuals.enemyhit)
        return;
    
    long now = GetEpochTime();
    lastHitmarkerTimestamp = now;
    damages.insert(damages.begin(), std::pair<int, long>(event->GetInt("dmg_health"), now));
    
    pCvar->ConsoleColorPrintf(Color::Green(), "[DEAD] Player hurt.");
    pEngine->ExecuteClientCmd("play buttons\\arena_switch_press_02.wav");
    
    
    
}
