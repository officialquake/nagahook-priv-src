//
//  antiaim.cpp
//  vHook
//

#include "antiaim.h"
#include "INetChannelInfo.h"
#define RandomFloat(min, max) (rand() % (max - min + 1) + min)

Vector atTargets;

bool isManual = false;
bool Swtich = false;

void antiResolverFlip(CUserCmd* cmd, C_BaseEntity* local)
{
    if(!vars.misc.antiResolverFlip)
        return;
    
    static bool antiResolverFlip = false;
    if (cmd->viewangles.y == local->GetLowerBodyYawTarget())
    {
        if (antiResolverFlip)
            cmd->viewangles.y += 60.f;
        else
            cmd->viewangles.y -= 60.f;
        
        antiResolverFlip = !antiResolverFlip;
    }
}

void resolverfucker(CUserCmd* cmd, C_BaseEntity* local)
{
    if(!vars.misc.resolverfucker)
        return;
    
    static bool resolverfucker = false;
    cmd->viewangles.y += atTargets.y +  30 + RandomInt(-30, 30);
    
    
    static float pDance = 0.0f;
    pDance += 45.0f;
    if (pDance > 100)
        pDance = 0.0f;
    else if (pDance > 75.f)
        cmd->viewangles.x = -50.f;
    else if (pDance < 75.f)
        cmd->viewangles.x = 50.f;
}

/**/

void turbojizzer(CUserCmd* cmd, C_BaseEntity* local)
{
    if(!vars.misc.turbojizzer)
        return;
    
    static bool turbo = false;
    if (cmd->viewangles.y == local->GetLowerBodyYawTarget())
    {
        if (turbo)
            cmd->viewangles.y -= 90.f;
        else
            cmd->viewangles.y += 90.f;
        
        turbo = !turbo;
    }
}

void doManual(CUserCmd* cmd){
    static bool left = false;
    static bool right = false;
    static bool back = false;
    
    bool flip = false;
    
    int Height, Width;
    pEngine->GetScreenSize(Height, Width);
    
    int x = Width / 2;
    int y = Height / 2;
    
    if (pInputSystem->IsButtonDown(KEY_LEFT)) {
        left = true; right = false; back = false;
    }
    else if (pInputSystem->IsButtonDown(KEY_RIGHT)) {
        left = false; right = true; back = false;
    }
    else if (pInputSystem->IsButtonDown(KEY_DOWN)) {
        left = false; right = false; back = true;
    }
    if ( left ){
        
        if (flip)
        {
            cmd->viewangles.y += 90.f - RandomFloat(5, vars.aimbot.jitter);
        }else
        {
            cmd->viewangles.y += 90 + RandomFloat(5, vars.aimbot.jitter);
        }
        
    }
    
    if ( right ){
        
        if (flip)
        {
            cmd->viewangles.y -= 90.f + RandomFloat(5, vars.aimbot.jitter);
        }else
        {
            cmd->viewangles.y -= 90 - RandomFloat(5, vars.aimbot.jitter);
        }
        
    }
    if ( back ){
        
        if (flip)
        {
            cmd->viewangles.y += 180.f - RandomFloat(5, vars.aimbot.jitter);
        }else
        {
            cmd->viewangles.y += 180.f + RandomFloat(5, vars.aimbot.jitter);
        }
        
    }
    flip = !flip;
    
}

void backjizzer(CUserCmd* cmd, C_BaseEntity* local)
{
    if(!vars.misc.backjizzer)
        return;
    
    static bool back = false;
    int random = rand() % 100;
    if (random < 98)
        cmd->viewangles.y -= 180;
    if (random < 15)
    {
        float change = -70 + (rand() % (int)(140 + 1));
    }
    if (random == 60)
    {
        float change = -90 + (rand() % (int)(180 + 1));
        cmd->viewangles.y += change;
    }
    
    back = !back;
}
void tank(CUserCmd* cmd, C_BaseEntity* local)
{
    
    if(!vars.misc.tank)
        return;
    static bool up = true;
    if (up) cmd->viewangles.x = 70;
    else cmd->viewangles.x = 88;
    up = !up;
}


void lby_spin(CUserCmd* cmd, C_BaseEntity* local)
{
    if(!vars.misc.lby_spin)
        return;
    float factor =  360.0 / M_PHI;
    factor = 2; // Change the value of (2) of what ever or take out “factor = 2;”
    cmd->viewangles.y = local->GetLowerBodyYawTarget() +fmodf(pGlobals->curtime * factor, 360.0);
}

/*if(!vars.misc.aaY) {
 return;
 
 static bool turbo = true;
 if (turbo)
 {
 cmd->viewangles.y -= 90.0f;
 turbo =  !turbo;
 }
 else
 {
 cmd->viewangles.y += 90.0f;
 turbo = !turbo;
 } //Pasted by Bellez :)
 
 */

float next_lby_update;
float old_lby;

float corrected_time( CUserCmd* ucmd, C_BaseEntity* local)
{
    static int g_tick = 0;
    static CUserCmd* g_pLastCmd = nullptr;
    if ( !g_pLastCmd || g_pLastCmd->hasbeenpredicted ) {
        g_tick = local->GetTickBase( );
    } else {
        // Required because prediction only runs on frames, not ticks
        // So if your framerate goes below tickrate, m_nTickBase won't update every tick
        ++g_tick;
    }
    g_pLastCmd = ucmd;
    float curtime = g_tick * pGlobals->interval_per_tick;
    return curtime;
}

bool lby_updated( CUserCmd* cmd, C_BaseEntity* local )
{
    float server_time = corrected_time(cmd, local);
    static bool once = true;
    
    if ( once && local->GetLowerBodyYawTarget( ) != old_lby ) {
        old_lby = local->GetLowerBodyYawTarget( );
        next_lby_update = server_time + 1.1;
        once = false;
    }
    
    bool on_ground = local->GetFlags( ) & FL_ONGROUND;
    
    if ( server_time >= next_lby_update && on_ground ) {
        next_lby_update = server_time + 1.1;
        return true;
    }
    
    return false;
}


void do_real2(CUserCmd* cmd, C_BaseEntity* local){
    
    static bool side1 = false;
    static bool side2 = false;
    static bool back = false;
    
    static bool bFlip = false;
    bFlip = !bFlip;
    
#define RandomInt(min, max) (rand() % (max - min + 1) + min)
    
    bool IsMovingOnInAir = {
        //Check if player has a velocity greater than 0 (moving) and if they are onground.
        !(local->GetFlags() & FL_ONGROUND)
    };
    
    
    if (pInputSystem->IsButtonDown(KEY_RIGHT)) {
        side1 = true;    side2 = false;    back = false;
    }
    if (pInputSystem->IsButtonDown(KEY_LEFT)) {
        side1 = false;    side2 = true;    back = false;
    }
    if (pInputSystem->IsButtonDown(KEY_DOWN)) {
        side1 = false;    side2 = false;    back = true;
    }
    
    if ( side1 ){
        cmd->viewangles.y += -90.f;
    }
    
    if ( side2 ){
        cmd->viewangles.y += 90.f;
    }
    if ( back ){
        cmd->viewangles.y += 179.f;
    }
    
    if (lby_updated(cmd, local)) {
        cmd->viewangles.y += 115.f; // less then 180 to prevent 979 animation, but less then 120 so its harder to predict
    }
    else if (lby_updated(cmd, local)){
        cmd->viewangles.y -= 115.f;
    }
    
    /*if (pInputSystem->IsButtonDown(KEY_X)){ // Should fuck people up trying to resolve you
     {
     {
     
     //something to do with lby and delta?
     cmd->viewangles.y += atTargets.y +  30 + RandomInt(-30, 30);
     
     
     static float pDance = 0.0f;
     pDance += 45.0f;
     if (pDance > 100)
     pDance = 0.0f;
     else if (pDance > 75.f)
     cmd->viewangles.x = -50.f;
     else if (pDance < 75.f)
     cmd->viewangles.x = 50.f;
     //now do yaw
     }
     }
     }*/
    
    /*if(IsMovingOnInAir){
     float factor;
     factor =  360.0 / M_PHI;
     factor *= 1.5;
     cmd->viewangles.y += -60;
     cmd->viewangles.y += fmodf(pGlobals->curtime * factor, 180.0);
     }*/
    
    
}

void do_real(CUserCmd* cmd, C_BaseEntity* local) {
    if (local->GetVelocity().Length2D() > 1.f) { // moving, lby starts updating at > 1.f velocity
        cmd->viewangles.y += 180.0f + rand() % (35 - -35 + 1 ) + -35;
    } else
    { // if we are standing still and our lby isn't updating
        if (lby_updated(cmd, local)) {
            cmd->viewangles.y = 90.f;
            cmd->viewangles.y += 115.f; // less then 180 to prevent 979 animation, but less then 120 so its harder to predict
        } else
        {
            cmd->viewangles.y = 90.f;
        }
    }
}

void do_fake(CUserCmd* cmd) {
    *bSendPacket = true;
    cmd->viewangles.y = rand() % (180 - -180 + 1 ) + -180;
}

void AngleVectors3(const Vector &angles, Vector& forward, Vector& right, Vector& up)
{
    float sr, sp, sy, cr, cp, cy;
    
    SinCos(DEG2RAD(angles[1]), &sy, &cy);
    SinCos(DEG2RAD(angles[0]), &sp, &cp);
    SinCos(DEG2RAD(angles[2]), &sr, &cr);
    
    forward.x = (cp * cy);
    forward.y = (cp * sy);
    forward.z = (-sp);
    right.x = (-1 * sr * sp * cy + -1 * cr * -sy);
    right.y = (-1 * sr * sp * sy + -1 * cr *  cy);
    right.z = (-1 * sr * cp);
    up.x = (cr * sp * cy + -sr * -sy);
    up.y = (cr * sp * sy + -sr * cy);
    up.z = (cr * cp);
}


float Freestand(C_BaseEntity* local, CUserCmd* cmd)
{
    if(!vars.misc.antiaim)
        return;
    
    if(vars.aimbot.freestand)
    {
        if(vars.aimbot.jitter > 0)
        {
        //Vector oldAngle = cmd->viewangles;
        bool flip = false;
        float Back, Right, Left;
        bool no_active = true;
        Vector src3D, dst3D, forward, right, up, src, dst;
        trace_t tr;
        Ray_t backray, rightray, leftray;
        CTraceFilter filter;
        
        Vector angles;
        pEngine->GetViewAngles(angles);
        
        AngleVectors3(angles, forward, right, up);
        
        filter.pSkip = local;
        src3D = local->GetVecOrigin() + local->GetVecViewOffset();
        dst3D = src3D + (forward * 384.f);
        
        backray.Init(src3D, dst3D);
        pEngineTrace->TraceRay(backray, MASK_SHOT, &filter, &tr);
        Back = (tr.endpos - tr.startpos).Length();
        
        rightray.Init(src3D + right * 35.f, dst3D + right * 35.f);
        pEngineTrace->TraceRay(rightray, MASK_SHOT, &filter, &tr);
        Right = (tr.endpos - tr.startpos).Length();
        
        leftray.Init(src3D - right * 35.f, dst3D - right * 35.f);
        pEngineTrace->TraceRay(leftray, MASK_SHOT, &filter, &tr);
        Left = (tr.endpos - tr.startpos).Length();
        
        if (Left > Right){
            
            if (flip)
            {
                cmd->viewangles.y -= 90.f - RandomFloat(5, vars.aimbot.jitter);
            }
            else
            {
                cmd->viewangles.y -= 90 + RandomFloat(5, vars.aimbot.jitter);
            }
            
        }else if (Right > Left){
            
            if (flip)
            {
                cmd->viewangles.y += 90.f - RandomFloat(5, vars.aimbot.jitter);
            }
            else
            {
                cmd->viewangles.y += 90 + RandomFloat(5, vars.aimbot.jitter);
            }
            
        }else if (Back > Right || Back > Left){
            
            if (flip)
            {
                cmd->viewangles.y = 180.f - RandomFloat(5, vars.aimbot.jitter);
            }
            else
            {
                cmd->viewangles.y = 180 + RandomFloat(5, vars.aimbot.jitter);
            }
            
        } else if(no_active){
            
            if (flip)
            {
                cmd->viewangles.y += 180.f - RandomFloat(5, vars.aimbot.jitter);
            }
            else
            {
                cmd->viewangles.y += 180 + RandomFloat(5, vars.aimbot.jitter);
            }
            
        }
        flip = !flip;
        return 0;
        
        if(!vars.misc.antiaim)
        {
            
            if(!vars.aimbot.freestand){
                doManual(cmd);
                isManual = true;
            }
            else{
                Freestand(local, cmd);
                isManual = false;
            }
            
        }
        cmd->viewangles.ClampAngles();
    }
    }
}

void DoAntiaim(CUserCmd* cmd, C_BaseEntity* local, C_BaseCombatWeapon* weapon, bool& bPacket)
{
    
    if (!vars.misc.antiaim)
        return;
    
    if (!local || !local->GetAlive())
        return;
    
    if (weapon->IsGrenade())
        return;
    
    
    static bool fakeswitch = false;
    static bool bFlip = false;
    static int fakeTick = 0;
    bool bAttack = true;
    bFlip = !bFlip;
    int maxJitter;
    int random;
    float temp;
    float factor;
    fakeTick++;
    
    if (weapon->GetNextPrimaryAttack() - pGlobals->interval_per_tick > local->GetTickBase() * pGlobals->interval_per_tick)
        bAttack = false;
    
    if(cmd->buttons & IN_ATTACK && (bAttack)) {
        bPacket = false;
    } else {
        bPacket = true;
        
        if (vars.misc.fakeaa) {
            fakeswitch = !fakeswitch;
            if (fakeswitch)
                bPacket = false;
            else
                bPacket = true;
        }
        
        if(vars.misc.aaX > 0) {
            if(vars.misc.aaX == VIEW_ANTIAIM_PITCH::Down){
                cmd->viewangles.x = 89;
            }
            if(vars.misc.aaX == VIEW_ANTIAIM_PITCH::Up) {
                cmd->viewangles.x = -89;
            }
        }
        if(vars.misc.aaY > 0) {
            if(vars.misc.aaY == VIEW_ANTIAIM_YAW::Backwards) {
                cmd->viewangles.y = 180;
            }
            if(vars.misc.aaY == VIEW_ANTIAIM_YAW::Jitter) {
                static bool bjitter;
                cmd->viewangles.y = bjitter ? 90 : -90;
                bjitter = !bjitter;
            }
            if(vars.misc.aaY == VIEW_ANTIAIM_YAW::FakeStatic) {
                static bool f_flip = true;
                f_flip = !f_flip;
                
                if (f_flip) {
                    *bSendPacket = false;
                    cmd->viewangles.y += 50.000000f;
                } else {
                    *bSendPacket = false;
                    cmd->viewangles.y -= 70.000000f;
                }
                
                if (!f_flip) {
                    *bSendPacket = true;
                    cmd->viewangles.y += 212.000000f;;
                } else if (!f_flip) {
                    *bSendPacket = true;
                    cmd->viewangles.y -= 180.000000f;
                }
            }
            if(vars.misc.aaY == VIEW_ANTIAIM_YAW::FJitter) {
                if(fakeswitch) cmd->viewangles.y = 90; else cmd->viewangles.y = local->GetLowerBodyYawTarget();
            }
            if(vars.misc.aaY == VIEW_ANTIAIM_YAW::SlowSpin) {
                factor =  360.0 / M_PHI;
                cmd->viewangles.y = fmodf(pGlobals->curtime * factor, 360.0);
            }
            if(vars.misc.aaY == VIEW_ANTIAIM_YAW::FastSpin) {
                factor =  360.0 / M_PHI;
                factor *= 25;
                cmd->viewangles.y = fmodf(pGlobals->curtime * factor, 360.0);
            }
            if(vars.misc.aaY == VIEW_ANTIAIM_YAW::RandomBackJitter) {
                cmd->viewangles.y -= 180;
                random = rand() % 100;
                maxJitter = rand() % (85-70+1) + 70;
                temp = maxJitter - (rand() % maxJitter);
                if(random < 35 + (rand() % 15))
                    cmd->viewangles.y -= temp;
                else if(random < 85 + (rand()% 15))
                    cmd->viewangles.y += temp;
            }
            if(vars.misc.aaY == VIEW_ANTIAIM_YAW::BackJitter) {
                int random = rand() % 100;
                if (random < 98)
                    cmd->viewangles.y -= 180;
                if (random < 15) {
                    float change = -70 + (rand() % (int) (140 + 1));
                    cmd->viewangles.y += change;
                }
                if (random == 69) {
                    float change = -90 + (rand() % (int) ( 180 + 1));
                    cmd->viewangles.y += change;
                }
            }
            if(vars.misc.aaY == VIEW_ANTIAIM_YAW::LowerYaw) { // Twist
                if (vars.misc.fakeaa) {
                    if (!bSendPacket) {
                        if (fakeTick < 300)
                            cmd->viewangles.y += 67.57f;
                        else if (fakeTick > 300)
                            cmd->viewangles.y -= 67.15f;
                        if (fakeTick < 300)
                            cmd->viewangles.y += 67.57f;
                        else if (fakeTick > 300)
                            cmd->viewangles.y -= 67.15f;
                        if (fakeTick > 600)
                            fakeTick = 0;
                        
                    } else {
                        cmd->viewangles.y += 180.f;
                    }
                } else {
                    cmd->viewangles.y += 180.f;
                }
            }
            if(vars.misc.aaY == VIEW_ANTIAIM_YAW::SidewaysLeft) {
                fakeswitch ? cmd->viewangles.y = 90 : cmd->viewangles.y = atTargets.y;
            }
            if(vars.misc.aaY == VIEW_ANTIAIM_YAW::SidewaysRight) {
                fakeswitch ? cmd->viewangles.y = -90 : cmd->viewangles.y = atTargets.y;
            }
            if(vars.misc.aaY == VIEW_ANTIAIM_YAW::LBYBreaker) {
                QAngle angle_for_yaw;
                static int counter = 0;
                static int motion = 0;
                int ServerTime = (float)pGlobals->interval_per_tick * local->GetTickBase() * 2;
                bool flip = true;
                
                if(flip) {
                    if(counter & (48 == 0))
                        motion++;
                    int value = ServerTime % 2;
                    switch (value) {
                        case 0:cmd->viewangles.y = local->GetLowerBodyYawTarget() - 90.00f > 35 ? local->GetLowerBodyYawTarget() - 180.f : local->GetLowerBodyYawTarget() - 90.f; break;
                            *bSendPacket = false;
                        case 1:cmd->viewangles.y = local->GetLowerBodyYawTarget() + 90.00f > 35 ? local->GetLowerBodyYawTarget() - 90.f : local->GetLowerBodyYawTarget() + 90.f; break;
                            *bSendPacket = true;
                    }
                    counter++;
                } else {
                    if(counter % 48 == 0)
                        motion++;
                    int value = ServerTime % 2;
                    switch (value) {
                        case 0:cmd->viewangles.y = angle_for_yaw.y + (rand() % 100 > 33 ? (rand() % 50 > 13 ? (rand() % 20 + 40) : -(rand() % 20 + 40)) : (rand() % 100 > 71 ? (rand() % 20 + 150) : -(rand() % 20 + 150))); break;
                            *bSendPacket = false;
                        case 1:cmd->viewangles.y = angle_for_yaw.y + (rand() % 100 > 33 ? (rand() % 50 > 13 ? (rand() % 20 + 40) : -(rand() % 20 + 40)) : (rand() % 100 > 71 ? (rand() % 20 + 150) : -(rand() % 20 + 150))); break;
                            *bSendPacket = true;
                    }
                    counter++;
                }
            }
            if(vars.misc.FaaY > 0 && (vars.misc.fakeaa && bPacket)) {
                if(vars.misc.FaaY == VIEW_ANTIIAIM_FYAW::FakeSpin){
                    int random = rand() % 100;
                    int random2 = rand() % 1000;
                    static bool dir;
                    static float current_y = cmd->viewangles.y;
                    float server_time = local->GetTickBase() * pGlobals->interval_per_tick;
                    
                    if (bSendPacket) {
                        cmd->viewangles.y = (float)(fmod(server_time / 0.39f * 360.0f, 360.0f));
                    } else {
                        if (random == 1) dir = !dir;
                        if (dir)
                            current_y -= 100.9;
                        else
                            current_y += 100.9;
                        cmd->viewangles.y = current_y;
                        if (random == random2)
                            cmd->viewangles.y -= random;
                    }
                }
                if(vars.misc.FaaY == VIEW_ANTIIAIM_FYAW::FakeLBYHook) {
                    static bool ySwitch;
                    static bool jbool;
                    static bool jboolt;
                    ySwitch = !ySwitch;
                    jbool = !jbool;
                    jboolt = !jbool;
                    if (jboolt) {
                        *bSendPacket = true;
                        cmd->viewangles.y = local->GetLowerBodyYawTarget() - 90.f;
                    } else {
                        *bSendPacket = true;
                        cmd->viewangles.y = local->GetLowerBodyYawTarget() + 90.f;
                    }
                }
                if(vars.misc.FaaY == VIEW_ANTIIAIM_FYAW::FakeTwoStep) {
                    static bool bFlipYaw;
                    float flInterval = pGlobals->interval_per_tick;
                    float flTickcount = cmd->tick_count;
                    float flTime = flInterval * flTickcount;
                    if (std::fmod(flTime, 1) == 0.f)
                        bFlipYaw = !bFlipYaw;
                    
                    if (bSendPacket)
                        cmd->viewangles.y += bFlipYaw ? 135.f : -135.f;
                    else
                        cmd->viewangles.y -= local->GetLowerBodyYawTarget() + (bFlipYaw ? -135.f : 135.f);
                }
                if(vars.misc.FaaY == VIEW_ANTIIAIM_FYAW::FakeLowerBody135) {
                    int flip = (int)floorf(pGlobals->curtime / 1.1) % 2;
                    static bool bFlipYaw;
                    float flInterval = pGlobals->interval_per_tick;
                    float flTickcount = cmd->tick_count;
                    float flTime = flInterval * flTickcount;
                    if (std::fmod(flTime, 1) == 0.f)
                        bFlipYaw = !bFlipYaw;
                    
                    if (bSendPacket) {
                        if (flip){
                            cmd->viewangles.y += bFlipYaw ? 135.f : -135.f;
                            
                        } else {
                            cmd->viewangles.y -= local->GetLowerBodyYawTarget() + (bFlipYaw ? 135.f : -135.f);
                        }
                    } else {
                        cmd->viewangles.y += 180.f;
                    }
                }
                if(vars.misc.FaaY == VIEW_ANTIIAIM_FYAW::FakeInverseRotation) {
                    float server_time = local->GetTickBase() * pGlobals->interval_per_tick;
                    
                    if (bSendPacket) {
                        cmd->viewangles.y += (float)(fmod(server_time / 0.80f * 360.0f, 360.0f));
                    } else {
                        cmd->viewangles.y -= (float)(fmod(server_time / 0.80f * 360.0f, 360.0f));
                    }
                }
                if(vars.misc.FaaY == VIEW_ANTIIAIM_FYAW::FakeJitter) {
                    static int jitterangle = 0;
                    
                    if (jitterangle <= 1) {
                        cmd->viewangles.y += 135;
                    } else if (jitterangle > 1 && jitterangle <= 3) {
                        cmd->viewangles.y += 225;
                    }
                    static int iChoked = -1;
                    iChoked++;
                    if (iChoked < 1){
                        *bSendPacket = true;
                        if (jitterangle <= 1) {
                            cmd->viewangles.y += 45;
                            jitterangle += 1;
                        } else if (jitterangle > 1 && jitterangle <= 3) {
                            cmd->viewangles.y -= 45;
                            jitterangle += 1;
                        } else {
                            jitterangle = 0;
                        }
                    } else {
                        *bSendPacket = false;
                        iChoked = -1;
                    }
                }
                if(vars.misc.FaaY == VIEW_ANTIIAIM_FYAW::FakeLBY) {
                    static bool flip_lby = false;
                    flip_lby = !flip_lby;
                    float server_time = local->GetTickBase() * pGlobals->interval_per_tick;
                    
                    if (flip_lby) {
                        *bSendPacket = false;
                        cmd->viewangles.y += (float)(fmod(server_time / 0.50f * 360.0f, 360.0f));
                    } else {
                        *bSendPacket = true;
                        cmd->viewangles.y -= local->GetLowerBodyYawTarget() + 180.00f;
                    }
                }
                if(vars.misc.FaaY == VIEW_ANTIIAIM_FYAW::FakeSideLBY) {
                    int i = 0; i < pEntList->GetHighestEntityIndex(); ++i;
                    C_BaseEntity* pEntity = pEntList->GetClientEntity(i);
                    //plocal = (C_BaseEntity*)(pEntList->GetClientEntity(pEngine->GetLocalPlayer()));
                    
                    static bool isMoving;
                    float PlayerIsMoving = abs(local->GetVelocity().Length());
                    if (PlayerIsMoving > 0.1) isMoving = true;
                    else if (PlayerIsMoving <= 0.1) isMoving = false;
                    
                    int flip = (int)floorf(pGlobals->curtime / 1.1) % 2;
                    static bool bFlipYaw;
                    float flInterval = pGlobals->interval_per_tick;
                    float flTickcount = cmd->tick_count;
                    float flTime = flInterval * flTickcount;
                    if (std::fmod(flTime, 1) == 0.f)
                        bFlipYaw = !bFlipYaw;
                    
                    if (PlayerIsMoving <= 0.1) {
                        if (bSendPacket) {
                            cmd->viewangles.y += 180.f;
                        } else {
                            if (flip) {
                                cmd->viewangles.y += bFlipYaw ? 90.f : -90.f;
                                
                            } else {
                                cmd->viewangles.y -= local->GetLowerBodyYawTarget() + (bFlipYaw ? 90.f : -90.f);
                            }
                        }
                    }
                    else if (PlayerIsMoving > 0.1) {
                        if (bSendPacket) {
                            cmd->viewangles.y -= 90.f;
                        } else {
                            cmd->viewangles.y += 90.f;
                        }
                    }
                }
            } // End Of FakeAA Yaw
        }
    }
    
    
    
    
    /*if (!bSendPacket) {
     do_real(cmd, local);
     } else {
     do_fake(cmd);
     }*/
    
    
    
}
