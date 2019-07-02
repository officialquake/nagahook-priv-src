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

void DoAntiaim(CUserCmd* cmd, C_BaseEntity* local, C_BaseCombatWeapon* weapon)
{
    
    if (!vars.misc.antiaim)
        return;
    
    if (!local || !local->GetAlive())
        return;
    
    if (!weapon)
        return;
    
    if (weapon->IsGrenade())
        return;
    
    static bool bFlip = false;
    bFlip = !bFlip;
    
    if (local->GetMoveType() == MOVETYPE_LADDER || local->GetMoveType() == MOVETYPE_NOCLIP)
        return;
    
    Vector angle = cmd->viewangles;
    
   
    
    if (cmd->buttons & IN_ATTACK || cmd->buttons & IN_USE)
        return;
    
    cmd->viewangles.x = 85.f;
    
    if (!vars.misc.fakelag) {
        *bSendPacket = cmd->command_number % 2;
    }
    
    if (!bSendPacket || vars.misc.fakeaa) {
        do_fake(cmd);
    } else {
        do_real2(cmd, local);
    }
    
    cmd->viewangles.ClampAngles();
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



/*void DoLegitAA(CUserCmd* cmd, C_BaseEntity* local, C_BaseCombatWeapon* weapon){
 if(vars.misc.legitaa)
 return;
 
 if(!local)
 return;
 
 if(!weapon)
 return;
 
 if(weapon->IsGrenade())
 return;
 
 if(local->GetMoveType() == MOVETYPE_LADDER)
 return;
 
 if(cmd->buttons & IN_ATTACK || cmd->buttons & IN_USE)
 return;
 
 if(!bSendPacket){
 //fake aa
 cmd->viewangles.y = 0.f;
 }else{
 //real aa
 #define RandomInt(min, max) (rand() % (max - min + 1) + min)
 {
 //something to do with lby and delta?
 cmd->viewangles.y = 90.f + RandomInt(-30, 30);
 
 }
 }
 }*/


/*
 void DoAntiaim(CUserCmd* cmd, C_BaseEntity* local, C_BaseCombatWeapon* weapon, bool& bPacket)
 {
 
 if (!vars.misc.antiaim)
 return;
 
 if (!local || !local->GetAlive())
 return;
 
 if (weapon->IsGrenade())
 return;
 
 bool Freestanding = GetBestHeadAngle;
 
 static bool fakeswitch = false;
 static bool bFlip = false;
 bool bAttack = true;
 bFlip = !bFlip;
 int maxJitter;
 int random;
 float temp;
 
 if (local->GetMoveType() == MOVETYPE_LADDER || local->GetMoveType() == MOVETYPE_NOCLIP)
 return;
 
 if (cmd->buttons & IN_ATTACK || cmd->buttons & IN_USE)
 return;
 
 if (!vars.misc.fakelag) {
 *bSendPacket = cmd->command_number % 2;
 }
 
 if(cmd->buttons & IN_ATTACK && (bAttack))
 {
 bPacket = false;
 }
 else
 {
 bPacket = true;
 
 if (vars.misc.fakeaa) // Fake AntiAim
 {
 fakeswitch = !fakeswitch;
 if (fakeswitch)
 bPacket = false;
 else
 bPacket = true;
 }
 
 if(vars.misc.aaX > 0)
 {
 bool clamp;
 if(vars.misc.aaX == VIEW_ANTIAIM_PITCH::Emotion)
 {
 cmd->viewangles.x = 89;
 }
 if(vars.misc.aaX == VIEW_ANTIAIM_PITCH::Dance){
 static float pDance = 0.0f;
 pDance += 45.0f;
 if (pDance > 100)
 pDance = 0.0f;
 else if (pDance > 75.f)
 cmd->viewangles.x = -89.f;
 else if (pDance < 75.f)
 cmd->viewangles.x = 89.f;
 }
 if(vars.misc.aaX == VIEW_ANTIAIM_PITCH::FakeDown){
 clamp = false;
 cmd->viewangles.x = bFlip ? 89.0f : 69.0f;;
 }
 if(vars.misc.aaX == VIEW_ANTIAIM_PITCH::FakeUp)
 {
 clamp = false;
 cmd->viewangles.x = bFlip ? 89.0f : -89.0f;;
 }
 
 } // END OF PITCH
 
 if(vars.misc.aaY > 0)
 {
 if(vars.misc.aaY == VIEW_ANTIAIM_YAW::Backwards)
 {
 cmd->viewangles.y -= 179.f;
 }
 
 if(vars.misc.aaY == VIEW_ANTIAIM_YAW::LowerYaw)
 {
 //cmd->viewangles.y = Freestanding; // I wished this fucking worked
 static int fakeTick = 0;
 fakeTick++;
 
 if (vars.misc.fakeaa)
 {
 if (!bSendPacket)
 {
 
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
 
 }
 else
 {
 cmd->viewangles.y += 180.f;
 }
 }
 else
 {
 cmd->viewangles.y -= 180.f;
 }
 }
 
 if(vars.misc.aaY == VIEW_ANTIAIM_YAW::manedgee)
 {
 bool air = !(local->GetFlags() & FL_ONGROUND); // in air
 
 static bool enabled     = false;
 static bool check       = false;
 float factor;
 
 if ( air ) // In air
 {
 factor =  360.0 / M_PHI;
 cmd->viewangles.y = fmodf(pGlobals->curtime * factor, 180.0);
 }
 else
 { // On ground
 if (pInputSystem->IsButtonDown(KEY_X))
 
 {
 if (!check)
 enabled = !enabled;
 check = true;
 }
 else
 {
 check = false;
 }
 
 if ( enabled )
 {
 cmd->viewangles.y += 90.f;
 }
 
 else
 {
 cmd->viewangles.y -= 90.0f;
 
 }
 
 if (lby_updated(cmd, local)) {
 cmd->viewangles.y += 115.f; // less then 180 to prevent 979 animation, but less then 120 so its harder to predict
 }
 }
 }
 
 if(vars.misc.aaY == VIEW_ANTIAIM_YAW::LBYbreak)
 {
 static bool side1 = false;
 static bool side2 = false;
 static bool back = false;
 
 if (pInputSystem->IsButtonDown(KEY_RIGHT)) {
 side1 = true;    side2 = false;    back = false;
 }
 if (pInputSystem->IsButtonDown(KEY_LEFT)) {
 side1 = false;    side2 = true;    back = false;
 }
 
 if ( side1 ){ // Right
 cmd->viewangles.y -= 90.f;
 }
 
 if ( side2 ){ // Left
 cmd->viewangles.y += 90;
 }
 
 if (lby_updated(cmd, local)) {
 cmd->viewangles.y += 115.f; // less then 180 to prevent 979 animation, but less then 120 so its harder to predict
 }
 
 if (pInputSystem->IsButtonDown(KEY_X)){ // Should fuck people up trying to resolve you
 int random = rand() % 100;
 if (random < 35 + (rand() % 15))
 {
 cmd->viewangles.y = rand() % (180 - -180 + 1 ) + -180;
 }
 
 else if (random < 85 + (rand() % 15))
 {
 cmd->viewangles.y = rand() % (360 - -360 + 1 ) + -360;
 }
 }
 }
 
 } // END OF YAW
 
 if( vars.misc.FaaY > 0 && ( (vars.misc.fakeaa && bPacket)|| !bSendPacket ) )
 {
 if(vars.misc.FaaY == VIEW_ANTIIAIM_FYAW::Rand) {
 cmd->viewangles.y = rand() % (180 - -180 + 1 ) + -180;
 }
 
 if(vars.misc.FaaY == VIEW_ANTIIAIM_FYAW::Rand2) {
 int random = rand() % 100;
 int maxJitter = rand() % (85 - 70 + 1) + 70;
 local->GetLowerBodyYawTarget() - (rand() % maxJitter);
 if (random < 35 + (rand() % 15))
 {
 cmd->viewangles.y -= local->GetLowerBodyYawTarget() - (rand() % maxJitter);;
 }
 
 else if (random < 85 + (rand() % 15))
 {
 cmd->viewangles.y += local->GetLowerBodyYawTarget() - (rand() % maxJitter);;
 }
 }
 
 if(vars.misc.FaaY == VIEW_ANTIIAIM_FYAW::Rand3){
 cmd->viewangles.y = rand() % (360 - -360 + 1 ) + -360;
 //cmd->viewangles.y = RandomFloat(35, 35);
 }
 
 if(vars.misc.FaaY == VIEW_ANTIIAIM_FYAW::lower135){
 static int ChokedPackets = -1;
 ChokedPackets++;
 if (ChokedPackets < 1)
 {
 *bSendPacket = true;
 cmd->viewangles.y += 180;
 ChokedPackets = -1;
 }
 else
 {
 *bSendPacket = false;
 ChokedPackets = -1;
 }
 }
 
 if(vars.misc.FaaY == VIEW_ANTIIAIM_FYAW::oneeighro){ // 180 rotation
 static float factor;
 static int ChokedPackets = -1;
 ChokedPackets++;
 if (ChokedPackets < 1)
 {
 *bSendPacket = true;
 
 ChokedPackets = -1;
 }
 else
 {
 *bSendPacket = false;
 ChokedPackets = -1;
 }
 }
 
 
 } // End Of FakeAA Yaw
 
 
 
 if( vars.misc.MaaY > 0)
 {
 float factor;
 
 if(vars.misc.MaaY == VIEW_ANTIIAIM_MYAW::LowerBody)
 {
 {
 static int fakeTick = 0;
 fakeTick++;
 
 if (vars.misc.fakeaa)
 {
 if (!bSendPacket)
 {
 
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
 
 }
 else
 {
 cmd->viewangles.y += 180.f;
 }
 }
 else
 {
 cmd->viewangles.y += 180.f;
 }
 
 }
 }
 
 if(vars.misc.MaaY == VIEW_ANTIIAIM_MYAW::BackJitter)
 {
 cmd->viewangles.y -= 180;
 random = rand() % 100;
 maxJitter = rand() % (85-70+1) + 70;
 temp = maxJitter - (rand() % maxJitter);
 if(random < 35 + (rand() % 15))
 cmd->viewangles.y -= temp;
 else if(random < 85 + (rand()% 15))
 cmd->viewangles.y += temp;
 }
 
 if(vars.misc.MaaY == VIEW_ANTIIAIM_MYAW::Rotate)
 {
 factor =  360.0 / M_PHI;
 cmd->viewangles.y = fmodf(pGlobals->curtime * factor, 180.0);
 }
 } // End of Moving on ground Yaw
 
 
 if(vars.misc.AaaY > 0)
 {
 float factor;
 
 if(vars.misc.AaaY == VIEW_ANTIIAIM_AYAW::LowerBod)
 {
 static int fakeTick = 0;
 fakeTick++;
 
 if (vars.misc.fakeaa)
 {
 if (!bSendPacket)
 {
 
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
 
 }
 else
 {
 cmd->viewangles.y += 180.f;
 }
 }
 else
 {
 cmd->viewangles.y += 180.f;
 }
 }
 if(vars.misc.AaaY == VIEW_ANTIIAIM_AYAW::Rotatee)
 {
 factor =  360.0 / M_PHI;
 cmd->viewangles.y = fmodf(pGlobals->curtime * factor, 180.0);
 }
 
 } // End of Moving in Air Yaw AA
 
 }
 cmd->viewangles.ClampAngles();
 }*/





/*if (!bSendPacket) {
 do_real(cmd, local);
 } else {
 do_fake(cmd);
 }*/




