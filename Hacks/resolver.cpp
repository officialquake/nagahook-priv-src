#include "main.h"
#include "antiaim.h"
#include <array>
#include "resolver.h"
RecvVarProxyFn OldProxy_Y; //OldProxy_X;

// Pitch Resolver
/*
 float AAA_Pitch(C_BaseEntity* entity){
 int index = entity->GetIndex();
 float angle = gCorrections[index].x;
 
 angle = 89;
 }
 */



float get_average_lby_standing_update_delta(C_BaseEntity* entity) {
    static float last_update_time[64];
    static float second_laste_update_time[64];
    static float oldlowerbody[64];
    int index = entity->GetIndex();
    float angle = gCorrections[index].y;
    float lby = static_cast<int>(fabs(angle - entity->GetLowerBodyYawTarget()));
    
    if (lby != oldlowerbody[entity->GetIndex()]) {
        second_laste_update_time[entity->GetIndex()] = last_update_time[entity->GetIndex()];
        last_update_time[entity->GetIndex()] = pGlobals->curtime;
        oldlowerbody[entity->GetIndex()] = lby;
    }
    
    return last_update_time[entity->GetIndex()] - second_laste_update_time[entity->GetIndex()];
}

bool lby_keeps_updating() {
    return get_average_lby_standing_update_delta;
}


float AAA_Yaw(C_BaseEntity* entity)
{
    int index = entity->GetIndex();
    float angle = gCorrections[index].y;
    
    bool IsMovingOnInAir = {
        //Check if player has a velocity greater than 0 (moving) and if they are onground.
        !(entity->GetFlags() & FL_ONGROUND)
    };
    
    bool Standing = {
        (entity->GetFlags() & FL_ONGROUND && entity->GetVelocity().Length2D() == 0.f)
    };
    
    bool MovingOnGround = {
        //Check if player has a velocity greater than 0 (moving) and if they are onground.
        entity->GetVelocity().Length2D() > 45.f && entity->GetFlags() & FL_ONGROUND
    };
    
    // Shit Fake Walk dectection
    bool maybeFakeWalking = {
        MovingOnGround && entity->GetVelocity().Length2D() < 36.0f
    };

    
    int shotmissed = 0;
    int shots = 1;
    
    if (vars.aimbot.yresolve == 1)
    { // rev(testing)
        
        static float old_simtime[65];// Using fake angles?
        static float storedhealth[65];
        
        
        bool badresolverlmao;
        
        if (shots >= 4)
        {
            if (entity->GetHealth() >= storedhealth[entity->GetIndex()] - 10) // lets compensate for nades n shit ghetto style
                badresolverlmao = true;
        }
        
        
        float last_simtime[64] = { 0.f };
        bool bFirstUpdate[64] = { false };
        float last_lby[64] = { 0.f };
        float last_lby_delta[64] = { 0.f };
        float large_lby_delta[64] = { 0.f };
        bool bSawUpdate[64] = { false };
        bool  was_moving[64] = { false };
        float flLbyFlickTime[64] = { 0.f };
        bool predLbyRecords[64] = { false };
        bool lbyRecords[64] = { false };
        
        
        
        for (auto i = 0; i < pEngine->GetMaxClients(); ++i) {
            const auto player = const_cast <C_BaseEntity*>(pEntList->GetClientEntity(i));
            
            auto local = pEntList->GetClientEntity(pEngine->GetLocalPlayer());
            
            
            if (!player || local == player || player->GetTeam() == local->GetTeam() || player->GetImmune() || player->GetDormant()) {
                last_simtime[i] = 0.f;
                bFirstUpdate[i] = false;
                last_lby[i] = 0.f;
                last_lby_delta[i] = 0.f;
                large_lby_delta[i] = 0.f;
                bSawUpdate[i] = false;
                was_moving[i] = false;
                flLbyFlickTime[i] = 0.f;
                predLbyRecords[i] = false;
                lbyRecords[i] = false;
                continue;
            }
            
            
            
            if (entity->GetSimulationTime() != old_simtime[entity->GetIndex()])
            {
                if (entity->GetLowerBodyYawTarget() != old_simtime[i]) //checking if cur lby is different to previous simrecord
                {
                    if (!bFirstUpdate[i]) // skip adding the first "change" after entity has been dormant/non-existant
                        bFirstUpdate[i] = true;
                    else
                    {
                        angle = entity->GetLowerBodyYawTarget();
                        lbyRecords[i];
                        predLbyRecords[i];
                        flLbyFlickTime[i] = old_simtime[i] + pGlobals->interval_per_tick; // previous simtime + 1 tick should give us the tick where they actually flicked. (Only first tick of a choke cycle gets used in anims)
                        bSawUpdate[i] = true; // we saw the update, we are good to add "predicted" updates, (didn't break when dormant)
                    }
                }
                //    simRecords[i].push_front(LagRecord(pEnt));
                
                // now comes predicting next lby update times, keeping in mind how an lby breaker works..
                if (old_simtime[i] - flLbyFlickTime[i] > 1.1 && bSawUpdate[i]) // previous sim update lby time delta over 1.1, meaning that next choked will be the break tick and -> the current sim is the next simupdate after that, we can shoot lby
                {
                    flLbyFlickTime[i] = old_simtime[i] + pGlobals->interval_per_tick; // save off the time where they actually did the break
                    predLbyRecords[i]; // save the actual current record, as this is the one we can shoot
                    angle = predLbyRecords[i];
                    
                }
            }
            else{
                angle = entity->GetLowerBodyYawTarget();
                
            }
        }
    }

    if(vars.aimbot.yresolve == 2){//lby(same as rev pre much)
        
        //Check if player has a velocity greater than 0 (moving) and if they are onground.
        float IsMovingOnInAir = (!(entity->GetFlags() & FL_ONGROUND));
        
        //Check if player has a velocity greater than 0 (moving) and if they are onground.
        float OnGround = (entity->GetFlags() & FL_ONGROUND);
        
        //Check if player has a velocity greater than 0 (moving) and if they are onground.
        bool MovingOnGround = (entity->GetVelocity().Length2D() > 45.f && entity->GetFlags() & FL_ONGROUND);
        
        // Fake Walk dectection
        float maybeFakeWalking = (MovingOnGround && entity->GetVelocity().Length2D() < 36.0f);
        
        //*lby should update if distance from *lby to eye angles exceeds 35 degrees
        float HasFakeHead = (abs(angle - entity->GetLowerBodyYawTarget()) > 35);
        
        //*lby should update if distance from *lby to eye angles less than 35 degrees
        float lbywithin35 = (abs(angle - entity->GetLowerBodyYawTarget()) < 35);
        
        
        if (IsMovingOnInAir)
        {
            switch (shots % 4)//logging hits for everyhitgroup//not anymore
            {
                case 1:
                    angle = entity->GetLowerBodyYawTarget() - 45;
                    break;
                case 2:
                    angle = entity->GetLowerBodyYawTarget() + 45;
                    break;
                case 3:
                    angle = entity->GetLowerBodyYawTarget() + 90;
                    break;
                case 4:
                    angle = entity->GetLowerBodyYawTarget() - 90;
                    break;
                    //continue;
            }
        }
        else//NOT MOVING
        {
            if (HasFakeHead)//*lby and eye angles arent synced eZ resolve
            {
                angle = angle - entity->GetLowerBodyYawTarget();
            }
            else {
                if (lbywithin35) //if *lby and eye angles subtracted < 35 then we assume that theyre using an *lby breaker
                {
                    switch (shotmissed % 5)
                    {
                            
                        case 0:
                            angle = entity->GetLowerBodyYawTarget() - 180;
                            break;
                        case 1:
                            angle = entity->GetLowerBodyYawTarget() - 180;
                            break;
                        case 2:
                            angle = entity->GetLowerBodyYawTarget() - 45;
                            break;
                        case 3:
                            angle = entity->GetLowerBodyYawTarget() + 45;
                            break;
                        case 4:
                            angle = entity->GetLowerBodyYawTarget() + 90;
                            break;
                        case 5:
                            angle = entity->GetLowerBodyYawTarget() - 90;
                            break;
                    }
                    
                    static float StoredYaw = 0;
                    static bool bLowerBodyIsUpdated = false;
                    if (entity->GetLowerBodyYawTarget() != StoredYaw) bLowerBodyIsUpdated = true;
                    else bLowerBodyIsUpdated = false;
                    if (bLowerBodyIsUpdated) StoredYaw = entity->GetLowerBodyYawTarget();
                    if (entity->GetFlags() & FL_ONGROUND && entity->GetVelocity().Length2D() != 0) angle = entity->GetLowerBodyYawTarget();
                    else
                    {
                        
                        {       // Yaw Resolver
                            // int num = Globals::Shots % 4 is a meme
                            int num = shotmissed % 4;
                            switch (num)
                            {
                                case 0:angle = angle + 180;
                                    break;
                                case 1:angle = angle - 90;
                                    break;
                                case 2:angle = angle + 90;
                                    break;
                                case 3:angle = angle + 179.95;
                                    break;
                                case 4:angle = angle - 179.95;
                                    break;
                                case 5:angle = angle + 40;
                                    break;
                                case 6:angle = angle - 40;
                                    break;
                                case 7:angle = angle + 30;
                                    break;
                                case 8:angle = angle - 30;
                                    break;
                                case 9:angle = angle + 15;
                                    break;
                                case 10:angle = angle - 15;
                                    break;
                            }
                        }
                    }
                }
                
            }
            
            if (OnGround) {
                if (maybeFakeWalking)
                {
                    
                    vector<int> hitboxes;
                    
                    //Baim
                    hitboxes.push_back(HITBOX_LOWER_CHEST);
                    hitboxes.push_back(HITBOX_BELLY);
                    hitboxes.push_back(HITBOX_PELVIS);
                    hitboxes.push_back(HITBOX_UPPER_CHEST);
                    // Feet
                    hitboxes.push_back(HITBOX_RIGHT_FOOT);
                    hitboxes.push_back(HITBOX_LEFT_FOOT);
                    hitboxes.push_back(HITBOX_RIGHT_CALF);
                    hitboxes.push_back(HITBOX_LEFT_CALF);
                    
                }
                angle = entity->GetLowerBodyYawTarget();
            }
            else
            {
                static bool isMoving;
                float PlayerIsMoving = abs(entity->GetVelocity().Length());
                if (PlayerIsMoving > 0.1) isMoving = true;
                else if (PlayerIsMoving <= 0.1) isMoving = false;
                
                static float oldlby = 0.0f;
                static bool bLowerBodyIsUpdated;
                float delta = angle - entity->GetLowerBodyYawTarget();
                if (entity->GetLowerBodyYawTarget() != oldlby) bLowerBodyIsUpdated = true;
                else bLowerBodyIsUpdated = false;
                
                if (bLowerBodyIsUpdated || isMoving || fabsf(delta) >= 35.0f)
                {
                    angle = entity->GetLowerBodyYawTarget();
                    entity->oldlby = entity->GetLowerBodyYawTarget();
                }
                
                else
                {
                    if (fabsf(delta) < 35.f && fabsf(delta) > 0.f)
                        angle = entity->GetLowerBodyYawTarget() + delta;
                }
                return angle;
            }
            
            static bool bLowerBodyIsUpdated;
            {
                
                if (shotmissed > 3 && shotmissed < 21)
                {
                    if (!bLowerBodyIsUpdated)
                    {
                        angle = entity->GetLowerBodyYawTarget();
                    }
                    else if (!bLowerBodyIsUpdated)
                    {
                        switch (shots % 4)
                        {
                            case 1: angle = - 30 + rand() % 45 - rand() % 51;
                                break;
                            case 2: angle = entity->GetLowerBodyYawTarget() + 20 - rand() % 35;
                                break;
                            case 3: angle = entity->GetLowerBodyYawTarget() + 45 % 30 - rand() % 90;
                                break;
                            case 4: angle = entity->GetLowerBodyYawTarget() - 90 - rand() % 90 - rand() % 40;
                                break;
                            case 5: angle = 160 - rand() % 90 - rand() % 40;
                                break;
                        }
                    }
                    else
                        angle = rand() % 180 - rand() % 45;
                }
                
                else if (shotmissed >= 2 && shotmissed <= 3)
                    
                {
                    if (bLowerBodyIsUpdated)
                    {
                        angle = entity->GetLowerBodyYawTarget();
                    }
                    else
                        angle = entity->GetLowerBodyYawTarget();
                }
                else
                {
                    if (bLowerBodyIsUpdated)
                    {
                        bool timer = false;
                        if (timer){
                            angle = entity->GetLowerBodyYawTarget() + rand() % 20;
                            timer = !timer;
                        }else {
                            angle = entity->GetLowerBodyYawTarget() - rand() % 100;
                        }
                    }
                    else
                    {
                        bool timer = false;
                        if (timer){
                            angle = entity->GetLowerBodyYawTarget() + rand() % 20;
                            timer = !timer;
                        } else {
                            angle = entity->GetLowerBodyYawTarget() - rand() % 20;
                        }
                    }
                }
            }
        }
        if(vars.aimbot.yresolve == 3){//lby(same as rev pre much)
            
#define RandomFloat(min, max) (rand() % (max - min + 1) + min)
            
            auto index = entity->GetIndex();
            
            
            static float LatestLowerBodyYaw[65];
            static float LatestLowerBodyYawUpdateTime[65];
            static float lbyproxytime;
            static float enemyLBYTimer[65];
            static float oldlowerbodyyawTest;
            
            
            static int missedLogHits[65];
            static float saveLastHeadshotFloat[65];
            static float saveLastBaimFloat[65];
            static float saveLastBaim30Float[65];
            static float enemysLastProxyTimer[65];
            static bool shotFakeHeadOnce[65];
            static int fakeshotMissedLast[65];
            static int ResolverStage[65];
            static int deltas[65];
            
            
            float deltadif = abs(angle - entity->GetLowerBodyYawTarget());
            lbyproxytime = enemysLastProxyTimer[entity->GetIndex()] + 0.2f;
            
            
            
            auto new_yaw = angle;
            float cur = pGlobals->curtime;
            float CurrentLowerbody = entity->GetLowerBodyYawTarget();
            bool is_fakewalk = entity->GetVelocity().Length2D() > 0 && entity->GetVelocity().Length2D() < 50;
            bool is_moving = entity->GetVelocity().Length2D() >= 50;
            bool is_standing = entity->GetVelocity().Length2D() == 0;
            bool is_onground = entity->GetFlags() & FL_ONGROUND;
            bool is_nospread = entity->GetVelocity().Length2D() > 250;
            
            
            if (is_onground)
            {
                
                
                
                if (entity->GetLowerBodyYawTarget() != LatestLowerBodyYaw[index] || (is_moving && !is_fakewalk && !is_standing))
                {
                    LatestLowerBodyYaw[index] = entity->GetLowerBodyYawTarget();
                    ResolverStage[index] = 1;
                    LatestLowerBodyYawUpdateTime[index] = pGlobals->curtime;
                    
                    return (entity->GetLowerBodyYawTarget());
                    
                }
                else
                {
                    if (is_fakewalk)
                    {
                        
                        if (deltadif && (cur, 10))
                        {
                            new_yaw = entity->GetLowerBodyYawTarget();
                            //Delta Changes
                            ResolverStage[index] = 2;
                        }
                        else if (entity->GetLowerBodyYawTarget() && (cur, 10))
                        {
                            new_yaw = entity->GetLowerBodyYawTarget();
                            //Lowerbody Changes
                            ResolverStage[index] = 3;
                        }
                        else {
                            new_yaw = angle + 180;
                            ResolverStage[index] = 21;
                        }
                        
                        
                    }
                    if (is_standing)
                    {
                        // Predict it only once a Round
                        if (shotFakeHeadOnce[index] == false) {
                            
                            if (((pGlobals->curtime - LatestLowerBodyYawUpdateTime[index]) >= 1.1))
                            {
                                new_yaw = CurrentLowerbody + 180;
                                ResolverStage[index] = 4;
                                shotFakeHeadOnce[index] = true;
                            }
                            
                        }
                        else
                        {
                            if (std::abs(LatestLowerBodyYaw[index] - CurrentLowerbody) <= 10)
                            {
                                int random = rand() % 10;
                                if (random < 6)
                                {
                                    new_yaw = CurrentLowerbody + RandomFloat(-10, 10);
                                    ResolverStage[index] = 1;
                                }
                                else
                                {
                                    new_yaw = CurrentLowerbody;
                                    ResolverStage[index] = 6;
                                }
                            }
                            else
                            {
                                if (deltadif && (cur, 10))
                                {
                                    new_yaw = deltas[entity->GetIndex()];
                                    ResolverStage[index] = 2;
                                }
                                else if (entity->GetLowerBodyYawTarget() && (cur, 10))
                                {
                                    new_yaw = entity->GetLowerBodyYawTarget();
                                    ResolverStage[index] = 3;
                                }
                            }
                        }
                        
                    }
                }
                
                
                if (missedLogHits[index] == 3 || missedLogHits[index] == 4) {
                    // Try Database Log Hits
                    ResolverStage[index] = 9;
                    
                    if (saveLastHeadshotFloat[index] != 0) {
                        new_yaw = saveLastHeadshotFloat[index];
                        
                    }
                    else if (saveLastBaimFloat[index] != 0) {
                        new_yaw = saveLastBaimFloat[index];
                        
                    }
                    else if (saveLastBaim30Float[index] != 0) {
                        new_yaw = saveLastBaim30Float[index];
                        
                    }
                    else {
                        
                        new_yaw = deltadif;
                        
                    }
                    
                }
                else if (missedLogHits[index] == 5 || missedLogHits[index] == 6 || missedLogHits[index] == 7) {
                    
                    ResolverStage[index] = 11;
                    
                    if (missedLogHits[index] == 5) {
                        new_yaw = deltadif - entity->GetLowerBodyYawTarget();
                    }
                    
                    if (missedLogHits[index] == 6 || missedLogHits[index] == 7) {
                        if (lbyproxytime != enemyLBYTimer[entity->GetIndex()] && abs(lbyproxytime - enemyLBYTimer[entity->GetIndex()]) > 0.8f) {
                            enemyLBYTimer[entity->GetIndex()] = lbyproxytime;
                            new_yaw = entity->GetLowerBodyYawTarget();
                            oldlowerbodyyawTest = entity->GetLowerBodyYawTarget();
                            
                        }
                        else {
                            
                            new_yaw = oldlowerbodyyawTest + deltadif;
                        }
                    }
                    
                }
                else if (missedLogHits[index] == 8) {
                    // Try Database Log Hits
                    ResolverStage[index] = 9;
                    
                    if (saveLastHeadshotFloat[index] != 0) {
                        
                        new_yaw = saveLastHeadshotFloat[index];
                        
                    }
                    else if (saveLastBaimFloat[index] != 0) {
                        
                        new_yaw = saveLastBaimFloat[index];
                        
                    }
                    else if (saveLastBaim30Float[index] != 0) {
                        
                        new_yaw = saveLastBaim30Float[index];
                        
                    }
                    else {
                        new_yaw = abs(entity->GetLowerBodyYawTarget() - angle);
                    }
                    
                }
                
                
                
                if (fakeshotMissedLast[index] <= 3) {
                    
                    if (abs(entity->GetLowerBodyYawTarget() - angle) > 35) {
                        // Enemy is using FakeAngle
                        new_yaw = angle - abs(entity->GetLowerBodyYawTarget() - angle);
                        ResolverStage[index] = 13;
                        fakeshotMissedLast[index] = missedLogHits[index];
                    }
                }
                
                
            }
            else
            {
                if (is_nospread)
                {
                    
                    if (missedLogHits[index] <= 10) {
                        
                        switch (shots % 4)
                        {
                            case 1:
                                new_yaw = CurrentLowerbody - 15;
                                break;
                            case 2:
                                new_yaw = CurrentLowerbody + 40;
                                break;
                            case 3:
                                new_yaw = CurrentLowerbody + 15;
                                break;
                            case 4:
                                new_yaw = CurrentLowerbody - 40;
                                break;
                        }
                        
                    }
                    else {
                        
                        new_yaw = RandomFloat(-180, 180);
                        
                    }
                    
                }
                else
                {
                    new_yaw = entity->GetLowerBodyYawTarget();
                    ResolverStage[index] = 7;
                    
                }
                
                if(IsMovingOnInAir)
                {
                    angle = entity->GetLowerBodyYawTarget();
                }
                
            }
            
            
            new_yaw = (new_yaw);
            return new_yaw;
        }
    }
    if(vars.aimbot.yresolve == 4){
        std::string strPitch = std::to_string(entity->GetEyeAngles()->x);
        
        if (entity->GetEyeAngles()->x < -179.f) entity->GetEyeAngles()->x += 360.f;
        else if (entity->GetEyeAngles()->x > 90.0 || entity->GetEyeAngles()->x < -90.0) entity->GetEyeAngles()->x = 89.f;
        else if (entity->GetEyeAngles()->x > 89.0 && entity->GetEyeAngles()->x < 91.0) entity->GetEyeAngles()->x -= 90.f;
        else if (entity->GetEyeAngles()->x > 179.0 && entity->GetEyeAngles()->x < 181.0) entity->GetEyeAngles()->x -= 180;
        else if (entity->GetEyeAngles()->x > -179.0 && entity->GetEyeAngles()->x < -181.0) entity->GetEyeAngles()->x += 180;
        else if (fabs(entity->GetEyeAngles()->x) == 0) entity->GetEyeAngles()->x = std::copysign(89.0f, entity->GetEyeAngles()->x);
    }
    if (vars.aimbot.yresolve == 6) {
        int i = entity->GetIndex();
        static float stored_lby[64];
        static float moving_lby[64];
        static bool bLowerBodyIsUpdated;
        if (entity->GetLowerBodyYawTarget() != stored_lby[i]) bLowerBodyIsUpdated = true;
        else bLowerBodyIsUpdated = false;
        
        if (bLowerBodyIsUpdated)
        {
            stored_lby[i] = entity->GetLowerBodyYawTarget();
        }
        
        if(Standing){
            angle = (rand() % 2) ?
            stored_lby[i] - 35:
            stored_lby[i] + 35;
        }
        else if(MovingOnGround){
            angle = entity->GetLowerBodyYawTarget();
            moving_lby[i] = entity->GetLowerBodyYawTarget();
        }
        else if(maybeFakeWalking){
            angle = (rand() % 2) ?
            moving_lby[i] - 15:
            moving_lby[i] + 15;
        }
        else if(IsMovingOnInAir){
            angle = stored_lby[i];
        }
        else{
            angle = entity->GetLowerBodyYawTarget();
        }
    }
    if(vars.aimbot.yresolve == 7){
        float movinglby[64];
        float lbytomovinglbydelta[64]; // long name idk what else to put
        bool onground = entity->GetFlags() & FL_ONGROUND;
        lbytomovinglbydelta[entity->GetIndex()] = entity->GetLowerBodyYawTarget() - lbytomovinglbydelta[entity->GetIndex()];
        
        if (entity->GetVelocity().Length2D() > 6 && entity->GetVelocity().Length2D() < 42) { // shitty ayyware fakewalk check better than nothing.
             entity->GetEyeAngles()->y = entity->GetLowerBodyYawTarget() + 180;
        }
        else if (entity->GetVelocity().Length2D() < 6 || entity->GetVelocity().Length2D() > 42) { // they are moving
            entity->GetEyeAngles()->y = entity->GetLowerBodyYawTarget();
            movinglby[entity->GetIndex()] = entity->GetLowerBodyYawTarget();
        }
        else if (lbytomovinglbydelta[entity->GetIndex()] > 50 && lbytomovinglbydelta[entity->GetIndex()] < -50) {// the 50 will allow you to have a 30 degree margin of error (do the math :))
            entity->GetEyeAngles()->y = movinglby[entity->GetIndex()];
        }
        else
            entity->GetEyeAngles()->y = entity->GetLowerBodyYawTarget();
    }
    return angle;
}


void FixYaw(const CRecvProxyData *pData, void *pStruct, void *pOut) {
    float flYaw = pData->m_Value.m_Float;
    
    int index = ((C_BaseEntity*)pStruct)->GetIndex();
    
    gCorrections[index].y = flYaw;
    
    OldProxy_Y(pData, pStruct, pOut);
}

void Resolver::FrameStageNotify(ClientFrameStage_t stage, C_BaseEntity* entity)
{
    if (!pEngine->IsInGame())
        return;
    
    C_BasePlayer* localplayer = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    if (!localplayer)
        return;
 
    static std::array<int, 64> oldMissedShots = { 0 };
    extern std::array<int, 64> missedShots;
    if (vars.aimbot.enabled && vars.aimbot.Yawresolver && vars.aimbot.yresolve > 0 && stage == ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START)
    {
        for (int i = 1; i < pEngine->GetMaxClients(); ++i)
        {
            C_BasePlayer* player = (C_BasePlayer*) pEntList->GetClientEntity(i);
            
            if (!player
                || player == localplayer
                || player->GetDormant()
                || !player->GetAlive()
                || player->GetImmune()
                || player->GetTeam() == localplayer->GetTeam())
                continue;
            
            CCSGOAnimState* animState = player->GetAnimState();
            if (!animState)
                continue;
            if(vars.aimbot.yresolve != 5)
                continue;
            
            float maxDelta = AntiAim::GetMaxxDelta(animState);
            int missedShot = LogShots::missedShots[player->GetIndex() - 1];
            int oldMissedShot = oldMissedShots[player->GetIndex() - 1];
            
            if (missedShot <= oldMissedShot)
                continue;
            
            //player->GetEyeAngles()->y = *player->GetLowerBodyYawTarget();
            switch (missedShot % 5)
            {
                case 0:
                    entity->GetEyeAngless()->y -= 0;
                    break;
                case 1:
                    entity->GetEyeAngless()->y -= maxDelta;
                    break;
                case 2:
                    entity->GetEyeAngless()->y += maxDelta;
                    break;
                case 3:
                    entity->GetEyeAngless()->y -= maxDelta / 2;
                    break;
                case 4:
                    entity->GetEyeAngless()->y += maxDelta / 2;
                    break;
            }
        }
    }
    else if (stage == ClientFrameStage_t::FRAME_RENDER_END)
    {
        oldMissedShots = LogShots::missedShots;
    }
}

void Resolver::PostFrameStageNotify(ClientFrameStage_t stage)
{
}

/*void Resolver1::FrameStageNotify1(ClientFrameStage_t stage, C_BaseEntity* entity)
{
    if (!pEngine->IsInGame())
        return;
    
    C_BasePlayer* localplayer = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    if (!localplayer)
        return;
    
    //static std::array<int, 64> oldMissedShots = { 0 };
    //extern std::array<int, 64> missedShots;
    if (stage == ClientFrameStage_t::FRAME_NET_UPDATE_POSTDATAUPDATE_START)
    {
        for (int i = 1; i < pEngine->GetMaxClients(); ++i)
        {
            C_BasePlayer* player = (C_BasePlayer*) pEntList->GetClientEntity(i);
           
           
            
            if (!player
                || player == localplayer
                || player->GetDormant()
                || !player->GetAlive()
                || player->GetImmune()
                || player->GetTeam() == localplayer->GetTeam())
                continue;
            
            //player_info_t entityInformation;
            //spEngine->GetPlayerInfo(i, &entityInformation);
             CCSGOAnimState* animState = player->GetAnimState();
            
            if (vars.aimbot.yresolve != 6)
                continue;
            float maxDelta = AntiAim::GetMaxxDelta(animState);
            
            //player_data.push_back(std::pair<C_BasePlayer*, QAngle>(player, *player->GetEyeAngles()));
            
            //player->GetEyeAngles()->y = *player->GetLowerBodyYawTarget();
            entity->GetEyeAngless()->y = (rand() % 2) ?
            entity->GetEyeAngless()->y + (maxDelta * 0.66f) :
            entity->GetEyeAngless()->y - (maxDelta * 0.66f);
        }
    }
    else if (stage == ClientFrameStage_t::FRAME_RENDER_END)
    {
    
    }
}

void Resolver1::PostFrameStageNotify1(ClientFrameStage_t stage)
{
}*/
