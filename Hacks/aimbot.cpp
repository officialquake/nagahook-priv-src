//
//  aimbot.cpp
//  vHook
//

#include "aimbot.h"
#include "autoshoot.h"
#include "antiaim.h"
#include "autowall.h"
#include "autostop.hpp"


C_BaseEntity* Aimbot::curTarget = nullptr;
#define RandomFloat(min, max) (rand() % (max - min + 1) + min)

int MakeHitscan(C_BaseEntity* entity)
{
    vector<int> hitboxes;
    
    
    
    
    
    if(vars.aimbot.hitscan > 0)
    {
        if(vars.aimbot.baimhp){
            int huso = (entity->GetHealth());
            int health = vars.aimbot.baimxhp;
            
            if (huso < health) {
                
                hitboxes.push_back(HITBOX_PELVIS);
                hitboxes.push_back(HITBOX_BELLY);
                hitboxes.push_back(HITBOX_THORAX);
                hitboxes.push_back(HITBOX_LOWER_CHEST);
                hitboxes.push_back(HITBOX_UPPER_CHEST);
                hitboxes.push_back(HITBOX_RIGHT_THIGH);
                hitboxes.push_back(HITBOX_LEFT_THIGH);
                hitboxes.push_back(HITBOX_RIGHT_CALF);
                hitboxes.push_back(HITBOX_LEFT_CALF);
                hitboxes.push_back(HITBOX_RIGHT_FOOT);
                hitboxes.push_back(HITBOX_LEFT_FOOT);
                hitboxes.push_back(HITBOX_RIGHT_HAND);
                hitboxes.push_back(HITBOX_LEFT_HAND);
                hitboxes.push_back(HITBOX_RIGHT_UPPER_ARM);
                hitboxes.push_back(HITBOX_RIGHT_FOREARM);
                hitboxes.push_back(HITBOX_LEFT_UPPER_ARM);
                hitboxes.push_back(HITBOX_LEFT_FOREARM);
            }
        }
        
        if (vars.aimbot.hitscantype == HITSCAN::low)
        { // low
            hitboxes.push_back(HITBOX_HEAD);
            hitboxes.push_back(HITBOX_NECK);
            hitboxes.push_back(HITBOX_PELVIS);
            hitboxes.push_back(HITBOX_BELLY);
            hitboxes.push_back(HITBOX_THORAX);
            hitboxes.push_back(HITBOX_LOWER_CHEST);
            hitboxes.push_back(HITBOX_UPPER_CHEST);
        }
        if (vars.aimbot.hitscantype == HITSCAN::normal)
        { //normal
            hitboxes.push_back(HITBOX_HEAD);
            hitboxes.push_back(HITBOX_NECK);
            hitboxes.push_back(HITBOX_BELLY);
            hitboxes.push_back(HITBOX_PELVIS);
            hitboxes.push_back(HITBOX_LOWER_CHEST);
            hitboxes.push_back(HITBOX_UPPER_CHEST);
            hitboxes.push_back(HITBOX_RIGHT_UPPER_ARM);
            hitboxes.push_back(HITBOX_LEFT_UPPER_ARM);
            hitboxes.push_back(HITBOX_RIGHT_THIGH);
            hitboxes.push_back(HITBOX_LEFT_THIGH);
            
        }
        if (vars.aimbot.hitscantype == HITSCAN::high)
        { //high
            hitboxes.push_back(HITBOX_HEAD);
            hitboxes.push_back(HITBOX_NECK);
            hitboxes.push_back(HITBOX_BELLY);
            hitboxes.push_back(HITBOX_UPPER_CHEST);
            hitboxes.push_back(HITBOX_RIGHT_UPPER_ARM);
            hitboxes.push_back(HITBOX_LEFT_UPPER_ARM);
            hitboxes.push_back(HITBOX_RIGHT_THIGH);
            hitboxes.push_back(HITBOX_LEFT_THIGH);
            hitboxes.push_back(HITBOX_RIGHT_CALF);
            hitboxes.push_back(HITBOX_LEFT_CALF);
            hitboxes.push_back(HITBOX_LEFT_FOREARM);
            hitboxes.push_back(HITBOX_RIGHT_FOREARM);
        }
        
        if (vars.aimbot.hitscantype == HITSCAN::extreme)
        {
            //extreme
            hitboxes.push_back(HITBOX_HEAD);
            hitboxes.push_back(HITBOX_NECK);
            hitboxes.push_back(HITBOX_PELVIS);
            hitboxes.push_back(HITBOX_BELLY);
            hitboxes.push_back(HITBOX_THORAX);
            hitboxes.push_back(HITBOX_LOWER_CHEST);
            hitboxes.push_back(HITBOX_UPPER_CHEST);
            hitboxes.push_back(HITBOX_RIGHT_THIGH);
            hitboxes.push_back(HITBOX_LEFT_THIGH);
            hitboxes.push_back(HITBOX_RIGHT_CALF);
            hitboxes.push_back(HITBOX_LEFT_CALF);
            hitboxes.push_back(HITBOX_RIGHT_FOOT);
            hitboxes.push_back(HITBOX_LEFT_FOOT);
            hitboxes.push_back(HITBOX_RIGHT_HAND);
            hitboxes.push_back(HITBOX_LEFT_HAND);
            hitboxes.push_back(HITBOX_RIGHT_UPPER_ARM);
            hitboxes.push_back(HITBOX_RIGHT_FOREARM);
            hitboxes.push_back(HITBOX_LEFT_UPPER_ARM);
            hitboxes.push_back(HITBOX_LEFT_FOREARM);
        }
        if (vars.aimbot.hitscantype == HITSCAN::baim)
        {
            hitboxes.push_back(HITBOX_PELVIS);
            hitboxes.push_back(HITBOX_BELLY);
            hitboxes.push_back(HITBOX_THORAX);
            hitboxes.push_back(HITBOX_LOWER_CHEST);
            hitboxes.push_back(HITBOX_UPPER_CHEST);
        }
    }
    
    
    
    
    
    
    
    if(vars.aimbot.hitscan)
    {
        
        int highestdamage_hitbox = 0;
        int highestdamage = 0;
        
        for(auto hit : hitboxes)
        {
            Vector vDest = GetHitboxPosition(entity, hit);
            float thisDamage = 0.f;
            Autowall::FireBulletData data;
            
            thisDamage = Autowall::GetDamage(vDest, true, data);
            
            if(thisDamage > highestdamage)
            {
                highestdamage = thisDamage;
                highestdamage_hitbox = hit;
            }
            
        }
        
        return highestdamage_hitbox;
    }
    else
    {
        return vars.aimbot.hitbox;
    }
    
}





void Hitchance(C_BaseEntity* pLocal, C_BaseCombatWeapon* pWeapon)
{
    if(vars.aimbot.hitchance)
    {
        float hitchance = 101;
        if (!pWeapon) return 0;
        if(vars.aimbot.accuracyhithcance > 1)
        {
            float inaccuracy = pWeapon->GetInaccuracy();
            if (inaccuracy == 0) inaccuracy = 0.0000001;
            inaccuracy = 1 / inaccuracy;
            hitchance = inaccuracy;
        }
        return hitchance;
    }
}

/*bool HitChance(Vector bestSpot, C_BasePlayer* player, C_BaseCombatWeapon* activeWeapon)
{
    C_BaseEntity* localplayer = pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    Vector src = localplayer->GetEyePosition();
    QAngle angle = CalcAngle(src, bestSpot);
    int hitCount = 0;
    int NeededHits = static_cast<int>(150.f * (vars.aimbot.accuracyhithcance / 100.f));
    
    activeWeapon->UpdateAccuracyPenalty();
    float weap_spread = activeWeapon->GetSpread();
    float weap_inaccuracy = activeWeapon->GetInaccuracy();
    
    for (int i = 0; i < 150; i++) {
        RandomSeed(i + 1); // if we can't calculate spread like game does, then at least use same functions XD
        float a = RandomFloat(0, 2 * (int)M_PI);
        float b = weap_spread * RandomFloat(0, 1);
        float c = RandomFloat(0, 2 * (int)M_PI);
        float d = weap_inaccuracy * RandomFloat(0, 1);
        
        Vector dir, dest;
        
        QAngle angles = angle;
        angles.x += (cos(a) * b) + (cos(c) * d);
        angles.y += (sin(a) * b) + (sin(c) * d);
        AngleVectors(angles, dir);
        dest = src + (dir * 8192);
        
        trace_t tr;
        Ray_t ray;
        CTraceFilter filter;
        
        ray.Init(src, dest);
        filter.pSkip = localplayer;
        pEngineTrace->TraceRay(ray, MASK_SHOT, &filter, &tr);
        
        C_BasePlayer* player = (C_BasePlayer*) tr.m_pEntityHit;
        
        if (tr.m_pEntityHit == player)
            hitCount++;
        
        if (static_cast<int>((static_cast<float>(hitCount) / 150.f) * 100.f) >= vars.aimbot.accuracyhithcance)
            return true;
        
        if ((150 - i + hitCount) < NeededHits)
            return false;
    }
    
    return false;
}*/




void DoAim(CUserCmd* pCmd, C_BaseEntity* local, C_BasePlayer* player, C_BaseCombatWeapon* weapon, float& flForward, float& flSide)
{
    
    if(!vars.aimbot.enabled)
        return;
    
    
    
    Vector eyepos = local->GetEyePosition();
    
    for(int i = 0; i < pEntList->GetHighestEntityIndex(); i++)
    {
        auto* entity = pEntList->GetClientEntity(i);
        
        if(!entity)
            continue;
        
        if(entity == local)
            continue;
        
        if(entity->GetTeam() == local->GetTeam())
            continue;
        
        if(entity->GetHealth() < 1)
            continue;
        
        if(entity->GetDormant())
            continue;
        
        if(entity->GetImmune())
            continue;
        
        if(weapon->GetAmmo() < 1)
            continue;
        
        if(weapon->IsKnife() || weapon->IsBomb())
            continue;
        
        if(gCorrections[entity->GetIndex()].whitelist)
            continue;
        
        Vector vFrom, vTo;
        
        Aimbot::curTarget = entity;
        
        vFrom = GetHitboxPosition(entity, MakeHitscan(entity));
        
        vTo = CalcAngle(eyepos, vFrom);
        
        auto isVISIBLE = IsVisible(local, entity);
        float getdmg = 0.f;
        Autowall::FireBulletData data;
        bool canHit = false;
        
        if(vars.aimbot.autowall)
        {
            getdmg = Autowall::GetDamage(vFrom, true, data);
            canHit = getdmg >= vars.aimbot.mindmg;
        }
    
        
        // FOV HERE
        
        atTargets = vTo;
        
        if(canHit || isVISIBLE || !vars.aimbot.enabled)
        {
            if(GetFOV(pCmd->viewangles, local->GetEyePosition(), vFrom) <= vars.aimbot.FovToPlayer)
            {
                if(vars.aimbot.autoshoot)
                {
                    //pCmd->buttons |= IN_ATTACK;
                    AutoShoot(local, weapon, pCmd);
                }
                if (local->GetVelocity().Length() >= (weapon->GetCSWpnData()->max_speed_alt * .34f) - 5 /*;)*/ && pInputSystem->IsButtonDown(MOUSE_MIDDLE) && vars.aimbot.autostop){
                    Autostop(pCmd, local);
                    
                }
                
                
                /*if(vars.aimbot.autozeus)
                 {
                 //pCmd->buttons |= IN_ATTACK;
                 AutoZeus(pCmd, local, weapon);
                 }*/
                if(vars.aimbot.autocock && vars.aimbot.autoshoot && vars.aimbot.enabled)
                {
                    //pCmd->buttons |= IN_ATTACK;
                    AutoCock(player, pCmd, weapon);
                }
                
                if (vars.aimbot.autoscope && weapon->IsSnipScope() && weapon->GetCSWpnData()->m_iZoomLevels > 0 && !local->IsScoped())
                {
                    pCmd->buttons |= IN_ATTACK2;
                }
                
                /*if(vars.aimbot.autostop)
                {
                    flForward = 0.f;
                    flSide = 0.f;
                }*/
                
                if(vars.aimbot.autocrouch)
                {
                    pCmd->buttons |= IN_DUCK;
                }
                
                
                
                
                
                
                bool bAttack = true;
                
                if (weapon->GetNextPrimaryAttack() - pGlobals->interval_per_tick > local->GetTickBase() * pGlobals->interval_per_tick)
                    bAttack = false;
                
                if(pCmd->buttons & IN_ATTACK)
                {
                    if(!vars.aimbot.silent)
                    {
                        pCmd->viewangles = vTo;
                        pEngine->SetViewAngles(pCmd->viewangles);
                    }
                    else
                    {
                        pCmd->viewangles = vTo;
                    }
                    
                }
                
            }
            
        }
        
    }
    
}













