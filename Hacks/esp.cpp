#include "main.h"

#include "esp.h"
#include "../Hacks/autowall.h"
#include "../Backtrack.hpp"
void DrawSkeleton(C_BaseEntity* pEntity, Color color){
    
    studiohdr_t* pStudioModel = pModelInfo->GetStudioModel( pEntity->GetModel() );
    
    if ( pStudioModel ) {
        
        static matrix3x4_t pBoneToWorldOut[128];
        
        if ( pEntity->SetupBones( pBoneToWorldOut, 128, 256, 0) )
        {
            for ( int i = 0; i < pStudioModel->numbones; i++ )
            {
                mstudiobone_t* pBone = pStudioModel->pBone( i );
                
                if ( !pBone || !( pBone->flags & 256 ) || pBone->parent == -1 )
                    continue;
                
                Vector vBone1 = pEntity->GetBonePosition(i);
                Vector vBoneOut1;
                
                Vector vBone2 = pEntity->GetBonePosition(pBone->parent);
                Vector vBoneOut2;
                
                if(WorldToScreen(vBone1, vBoneOut1) && WorldToScreen(vBone2, vBoneOut2)) {
                    draw->drawline(vBoneOut1.x, vBoneOut1.y, vBoneOut2.x, vBoneOut2.y, color);
                }
            }
        }
    }
}


Color GetColorBase(Color& col)
{
    return Color(col.r(), col.g(), col.b(), 255);
}



void DrawHealthbar(int x, int y, int w, int h, int health, Color color)
{
    if(health > 100)
    {
        health = 100;
    }
    int hw = h - ((h) * health) / 100;
    draw->fillrgba(x, y - 1, w, h + 2, Color(0, 0, 0, 200));
    draw->fillrgba(x, y + hw - 1, w, h - hw + 2, color);
    draw->drawbox(x, y - 1, w, h + 2, Color(0, 0, 0, 200));
    
    
}

void box3d(C_BaseEntity* entity, Color color) {
    
    Vector vOrigin = entity->GetVecOrigin();
    Vector min = entity->GetCollideable()->OBBMins() + vOrigin;
    Vector max = entity->GetCollideable()->OBBMaxs() + vOrigin;
    
    Vector points[] = { Vector(min.x, min.y, min.z),
        Vector(min.x, max.y, min.z),
        Vector(max.x, max.y, min.z),
        Vector(max.x, min.y, min.z),
        Vector(min.x, min.y, max.z),
        Vector(min.x, max.y, max.z),
        Vector(max.x, max.y, max.z),
        Vector(max.x, min.y, max.z) };
    
    int edges[12][2] = {
        { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 },
        { 4, 5 }, { 5, 6 }, { 6, 7 }, { 7, 4 },
        { 0, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 },
    };
    
    for (auto it : edges) {
        Vector p1, p2;
        if (pOverlay->ScreenPosition(points[it[0]], p1) || pOverlay->ScreenPosition(points[it[1]], p2))
            return;
        
    }
}

C_BaseCombatWeapon* getWeapon(C_BaseEntity* local) {
    auto hWeapon = local->GetActiveWeapon();
    if (!hWeapon)
        return;
    
    return (C_BaseCombatWeapon*)pEntList->GetClientEntityFromHandle(hWeapon);
}

void DrawDroppedWeapons(C_BaseCombatWeapon* weapon) {
    
    Vector vOrig = weapon->GetVecOrigin();
    int owner = weapon->GetOwner();
    
    if (owner > -1 || (vOrig.x == 0 && vOrig.y == 0 && vOrig.z == 0))
        return;
    
    string model = GetWeaponName(weapon);
    
    boxstruct wBox;
    
    if(DrawPlayerBox(weapon, wBox)) {
        draw->drawstring(wBox.x + wBox.w / 2, wBox.y, Color::White(), csgo_icons, model.c_str(), true);
        
        
    }
}

void grenadeESP(C_BaseEntity* entity){
    
    if(!vars.visuals.grenade)
        return;
    
    if(!strstr(entity->GetClientClass()->m_pNetworkName, "Projectile"))
        return;
    
    const model_t* model = entity->GetModel();
    
    if(!model)
        return;
    
    studiohdr_t* hdr = pModelInfo->GetStudioModel(model);
    
    if(!hdr || (!strstr(hdr->name, "thrown") && !strstr(hdr->name, "dropped")))
        return;
    
    Color color;
    char* name = nullptr;
    
    IMaterial* mats[32];
    pModelInfo->GetModelMaterials(model, hdr->numtextures, mats);
    for(int i = 0; i < hdr->numtextures; i++){
        IMaterial* mat = mats[i];
        
        if(!mat)
            continue;
        
        if(strstr(mat->GetName(), "flashbang")){
            color = Color(255, 235, 59, 255);
            name = "p";
            break;
        }
        if(strstr(mat->GetName(), "smoke")){
            color = Color(97, 97, 97, 255);
            name = "O";
            break;
        }
        if(strstr(mat->GetName(), "decoy")){
            color = Color(97, 97, 97, 255);
            name = "l";
            break;
        }
        if(strstr(mat->GetName(), "m67_grenade") || strstr(mat->GetName(), "hegrenade")){
            color = Color(244, 67, 54, 255);
            name = "t";
            break;
        }
        if(strstr(mat->GetName(), "incendiary")){
            color = Color(244, 67, 54, 255);
            name = "v";
            break;
        }
        if(strstr(mat->GetName(), "molotov")){
            color = Color(244, 67, 54, 255);
            name = "D";
        }
    }
    
    boxstruct nBox;
    
    if(DrawPlayerBox(entity, nBox)){
        draw->drawstring(nBox.x + nBox.w + 3, nBox.y - (nBox.h/2), Color::Yellow(), csgo_icons, name);
        box3d(entity, color);
    }
    
    
}



void DrawBombPlanted(C_BaseEntity* local, C_BasePlantedC4* bomb)
{
    if(!bomb->IsBombTicking())
        return;
    
    boxstruct Box;
    
    if(!DrawPlayerBox(bomb, Box))
        return;
    
    float flBlow    = bomb->GetBombTime();
    float bombTimer = flBlow - (pGlobals->interval_per_tick * local->GetTickBase());
    
    char buffer[128];
    
    if((local->HasDefuser() && flBlow < 5.25f) || (!local->HasDefuser() && flBlow < 10.25f))
        sprintf(buffer, "No time %.f", bombTimer);
    
    if((local->HasDefuser() && flBlow > 5.25f) || (!local->HasDefuser() && flBlow > 10.25f))
        sprintf(buffer, "Bomb %.f", bombTimer);
    
    if (bomb->IsBombDefused() || !bomb->IsBombTicking() || bombTimer <= 0.f)
        sprintf(buffer, "Bomb");
    
    draw->drawstring(Box.x, Box.y, Color(255, 0, 0, 255), espfont, buffer);
    
}

void DrawOtherESP() {
    // WIP
    if(!vars.visuals.enabled)
        return;
    
    if(vars.misc.antiscreenshot && pEngine->IsTakingScreenshot())
        return;
    
    int getscreenw, getscreenh;
    pEngine->GetScreenSize(getscreenw, getscreenh);
    
    C_BaseEntity* local = pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    
    for(int i = 0; i < pEntList->GetHighestEntityIndex(); i++)
    {
        auto* entity = pEntList->GetClientEntity(i);
        
        if(!entity)
            continue;
        
        int classID = entity->GetClientClass()->m_ClassID;
        C_BaseCombatWeapon* weapon = (C_BaseCombatWeapon*)entity;
        C_BasePlantedC4* pC4 = (C_BasePlantedC4*)entity;
        
        
        if(!weapon || !pC4)
            continue;
        
        if(vars.visuals.weapons) {
            if(classID != EClassIds::CBaseWeaponWorldModel) {
                if (strstr(entity->GetClientClass()->m_pNetworkName, "Weapon") || classID == EClassIds::CDEagle || classID == EClassIds::CAK47) {
                    DrawDroppedWeapons(weapon);
                }
            }
        }
        
        // Draw planted bomb
        if(vars.visuals.bombtimer && classID == CPlantedC4)
            DrawBombPlanted(local, pC4);
        
        if (vars.visuals.grenade)
            grenadeESP(entity);
        
        
        // Manual AA prediction
        /*if(vars.visuals.manualaa)
         {
         manualaa();
         }*/
        
    }
}

void DrawSpread() {
    
    if(!pEngine->IsInGame())
        return;
    
    if(!vars.misc.spreadcrosshair)
        return;
    
    
    float GetInaccuracy = 0.f;
    
    C_BasePlayer* localplayer = (C_BasePlayer*)pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    if (!localplayer)
        return;
    C_BaseCombatWeapon* activeWeapon = (C_BaseCombatWeapon*)pEntList->GetClientEntityFromHandle(localplayer->GetActiveWeapon());
    if (!activeWeapon)
        return;
    
    int w, h;
    pEngine->GetScreenSize(w, h);
    
    int crX = w / 2, crY = h / 2;
    int drX;
    int drY;
    
    char getInaccuracy[255];
    float flCone = activeWeapon->GetInaccuracy();
    float flSpread = activeWeapon->GetSpread();
    float flRadius = (flCone + flSpread) * 500.0f;
    auto accuracy = activeWeapon->GetInaccuracy() * 550.f; //3000
    //sprintf(getInaccuracy, "Accuracy: 100.f", activeWeapon->GetInaccuracy());
    
    draw->DrawFilledCircle(Vector2D(crX, crY), Color(24, 24, 24, 124), flRadius, 60);
    //draw->DrawFilledCircle(Vector2D(xs, ys), Color(24, 24, 24, 124), accuracy, 60);
    //draw->drawstring(10, h - 440, Color::Red(), tFont, getInaccuracy);
}

void DrawAngles(C_BaseEntity* local)
{
    //if (!pEngine->IsConnected() || !pEngine->IsInGame()) {
    
    if(!pEngine->IsInGame())
        return;
    
    if(!vars.visuals.antiaim_indicator )
        return;
    
    if(!vars.visuals.aaline)
        return;
    
    Vector src3D, dst3D, forward, src, dst;
    trace_t tr;
    Ray_t ray;
    CTraceFilter filter;
    
    filter.pSkip = local;
    src3D = local->GetVecOrigin();
    
    AngleVectors(Vector(0, YAW, 0), &forward);
    dst3D = src3D + (forward * 45.f);
    
    ray.Init(src3D, dst3D);
    
    pEngineTrace->TraceRay(ray, 0, &filter, &tr);
    
    if (!WorldToScreen(src3D, src) || !WorldToScreen(tr.endpos, dst))
        return;
    
    draw->Line(src.x, src.y, dst.x, dst.y, Color::Blue());
    
    if (vars.visuals.anglelinenames)
        draw->drawstring(dst.x, dst.y, Color::Blue(), espfont, "LBY");
    
    
    AngleVectors(Vector(0, local->GetLowerBodyYawTarget(), 0), &forward);
    dst3D = src3D + (forward * 45.f);
    
    ray.Init(src3D, dst3D);
    
    pEngineTrace->TraceRay(ray, 0, &filter, &tr);
    
    if (!WorldToScreen(src3D, src) || !WorldToScreen(tr.endpos, dst))
        return;
    
    draw->Line(src.x, src.y, dst.x, dst.y, Color(0, 255, 0, 255));
    
    if (vars.visuals.anglelinenames)
        draw->drawstring(dst.x, dst.y, Color(0, 255, 0, 255), espfont, "REAL");
}
//}


void DrawPlayerESP()
{
    if(!vars.visuals.enabled)
        return;
    if(vars.misc.antiscreenshot && pEngine->IsTakingScreenshot())
        return;
    
    int getscreenw, getscreenh;
    pEngine->GetScreenSize(getscreenw, getscreenh);
    
    auto* local = pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    for(int i = 0; i < pEntList->GetHighestEntityIndex(); i++)
    {
        auto* entity = pEntList->GetClientEntity(i);
        
        if(!entity)
            continue;
        
        if(entity->GetHealth() < 1)
            continue;
        
        if(entity->GetDormant())
            continue;
        
        if(entity->GetTeam() != 2 && entity->GetTeam() != 3)
            continue;
        
        if(vars.visuals.enemyonly && entity->GetTeam() == local->GetTeam())
            continue;
        
        player_info_t info;
        
        pEngine->GetPlayerInfo(i, &info);
        
        auto vis = IsVisible(local, entity);
        
        Color playercolor = [&]() -> Color
        {
            if(entity->GetTeam() == 3)
                return vis ? GetColorBase(vars.colors.ctbox) : GetColorBase(vars.colors.ctbox_ign);
            else if(entity->GetTeam() == 2)
                return vis ? GetColorBase(vars.colors.tbox) : GetColorBase(vars.colors.tbox_ign);
        }();
        
        boxstruct players;
        char getYaw[255], getPitch[255];
        
        sprintf(getYaw, "Y: %1.0f", entity->GetYawRotation());
        sprintf(getPitch, "X: %1.0f", entity->GetHeadRotation());
        
        Vector vFrom = GetHitboxPosition(entity, (int)HITBOX_HEAD);
        Vector vW2s;
        Vector vvvv;
        Vector origin = entity->GetVecOrigin();
        
        if(DrawPlayerBox(entity, players)) {
            
            /* Draw box */
            
            if(vars.visuals.box)
                draw->drawboxoutline(players.x, players.y, players.w, players.h, playercolor);
            
            /* Draw name */
            if(vars.visuals.name)
                draw->drawstring(players.x + players.w / 2, players.y - 12, Color::White(), espfont, info.name, true);
            
            /* Draw health bar */
            if(vars.visuals.health)
                DrawHealthbar(players.x - 5, players.y, 3, players.h, entity->GetHealth(), Color::Green());
            
            
            /* Draw health as text */
            if(vars.visuals.healthtext)
                draw->drawstring(players.x + players.w + 3, players.y + 1, Color::White(), espfont, std::to_string(entity->GetHealth()).c_str(), true);
            
            /* Draw amour bar */
            if(vars.visuals.armour)
                DrawHealthbar(players.x, players.y + players.h + 3, players.w, 2, entity->GetArmor(), Color(72, 136, 189, 255));
            
            /*if(vars.visuals.armortext)
             draw->drawstring(players.x + players.w / 2, players.y + players.h + 8, Color::White(), espfont, std::to_string(entity->GetArmor()).c_str(), true);*/
            
            if(vars.visuals.active) {
                string active = GetWeaponName(getWeapon(entity));
                draw->drawstring(players.x + players.w / 2, players.y + players.h + 5, Color::White(), csgo_icons, active.c_str());
                
                
            }
            
            /* Draw snaplines */
            if(vars.visuals.snapline)
                draw->drawline(getscreenw / 2, getscreenh / 2, players.x + players.w / 2, players.y + players.h, Color::Red());
            
            /* Draw skeleton */
            if(vars.visuals.skeleton)
                DrawSkeleton(entity, Color::Red());
            
            
            if(vars.visuals.defusing && entity->IsDefusing())
                draw->drawstring(players.x + players.w / 2, players.y - 27, Color::Red(), espfont, "DEFUSING", true);
            
            
            
            if(vars.visuals.rescuing && entity->IsGrabbingHostage())
                draw->drawstring(players.x + players.w / 2, players.y - 27, Color::Red(), espfont, "RESCUING", true);
            
            if(entity->IsRescuing())
                draw->drawstring(players.x + players.w / 2, players.y - 27, Color::Red(), espfont, "CARRYING", true);
            
        
            
            if((vars.visuals.scoped && entity->IsScoped()))
                draw->drawstring(players.x + players.w / 2, players.y - 27, Color::Red(), espfont, "SCOPING", true);
            if(vars.misc.radar){
                *entity->GetSpotted() = true;
            }
            if((entity->GetFlashDuration() - pGlobals->curtime > 2.0f))
                draw->drawstring(players.x + players.w / 2, players.y - 27, Color::Yellow(), espfont, "Flashed");
        }
        if (entity && entity != local && !entity->GetDormant())
        {
            if (entity->GetAlive())
            {
                if (vars.aimbot.backtrack)
                {
                    if (local->GetAlive())
                    {
                        for (int t = 0; t < 12; ++t)
                        {
                            Vector screenbacktrack[64][12];
                            
                            if (headPositions[i][t].simtime && headPositions[i][t].simtime + 1 > local->GetSimulationTime())
                            {
                                if (WorldToScreen(headPositions[i][t].hitboxPos, screenbacktrack[i][t]))
                                {
                                    
                                    pSurface->DrawSetColor(Color::Black());
                                    pSurface->DrawOutlinedRect(screenbacktrack[i][t].x, screenbacktrack[i][t].y, screenbacktrack[i][t].x + 2, screenbacktrack[i][t].y + 2);
                                    
                                    
                                }
                            }
                        }
                    }
                    else
                    {
                        memset(&headPositions[0][0], 0, sizeof(headPositions));
                    }
                }
            }
        }
    }
}

/* Display menu */
void pwnmymenu()
{
    if(pInputSystem->IsButtonDown(KEY_INSERT))
    {
        vars.menu = !vars.menu;
    }
}
