//
//  antiaim.cpp
//  vHook
//

#include "antiaim.h"
#include "INetChannelInfo.h"
#define RandomFloat(min, max) (rand() % (max - min + 1) + min)
static bool manualswitch = true;


Vector atTargets;

bool isManual = false;
bool Swtich = false;
static bool jitter2 = false;




void inline SinCos(float radians, float* sine, float* cosine)
{
    *sine = sin(radians);
    *cosine = cos(radians);
}




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

bool NextLBYUpdate2( CUserCmd* cmd, C_BaseEntity* local )
{
    float server_time = corrected_time(cmd, local);
    
    if (local->GetVelocity().Length2D() > 0.1f)
    {
        next_lby_update = server_time + 0.22 + pGlobals->interval_per_tick;
        return false;
    }
    
    if ((next_lby_update < server_time) && (local->GetFlags() & FL_ONGROUND) && local->GetVelocity().Length2D() < 1.f)
    {
        next_lby_update = server_time + 1.1 + pGlobals->interval_per_tick;
        return true;
    }
    
    return false;
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
void VectorAngles2(const Vector &vecForward, Vector &vecAngles)
{
    Vector vecView;
    if (vecForward[1] == 0.f && vecForward[0] == 0.f)
    {
        vecView[0] = 0.f;
        vecView[1] = 0.f;
    }
    else
    {
        vecView[1] = atan2(vecForward[1], vecForward[0]) * 180.f / M_PI;
        
        if (vecView[1] < 0.f)
            vecView[1] += 360.f;
        
        vecView[2] = sqrt(vecForward[0] * vecForward[0] + vecForward[1] * vecForward[1]);
        
        vecView[0] = atan2(vecForward[2], vecView[2]) * 180.f / M_PI;
    }
    
    vecAngles[0] = -vecView[0];
    vecAngles[1] = vecView[1];
    vecAngles[2] = 0.f;
}


void AngleVectors2(const Vector& qAngles, Vector& vecForward)
{
    float sp, sy, cp, cy;
    SinCos((float)(qAngles[1] * (M_PI / 180.f)), &sy, &cy);
    SinCos((float)(qAngles[0] * (M_PI / 180.f)), &sp, &cp);
    
    vecForward[0] = cp*cy;
    vecForward[1] = cp*sy;
    vecForward[2] = -sp;
}

bool EdgeAntiAim(C_BaseEntity* pLocalBaseEntity, CUserCmd* cmd, float flWall, float flCornor)
{
    Ray_t ray;
    trace_t tr;
    
    CTraceFilter traceFilter;
    traceFilter.pSkip = pLocalBaseEntity;
    
    auto bRetVal = false;
    auto vecCurPos = pLocalBaseEntity->GetEyePosition();
    
    for (float i = 0; i < 360; i++)
    {
        Vector vecDummy(10.f, cmd->viewangles.y, 0.f);
        vecDummy.y += i;
        
        NormalizeVector(vecDummy);
        
        Vector vecForward;
        AngleVectors2(vecDummy, vecForward);
        
        auto flLength = ((16.f + 3.f) + ((16.f + 3.f) * sin(DEG2RAD(10.f)))) + 7.f;
        vecForward *= flLength;
        
        ray.Init(vecCurPos, (vecCurPos + vecForward));
        pEngineTrace->TraceRay(ray, MASK_SHOT, (CTraceFilter *)&traceFilter, &tr);
        
        if (tr.fraction != 1.0f)
        {
            Vector qAngles;
            auto vecNegate = tr.plane.normal;
            
            vecNegate *= -1.f;
            VectorAngles2(vecNegate, qAngles);
            
            vecDummy.y = qAngles.y;
            NormalizeVector(vecDummy);
            trace_t leftTrace, rightTrace;
            
            Vector vecLeft;
            AngleVectors2(vecDummy + Vector(0.f, 30.f, 0.f), vecLeft);
            
            Vector vecRight;
            AngleVectors2(vecDummy - Vector(0.f, 30.f, 0.f), vecRight);
            
            vecLeft *= (flLength + (flLength * sin(DEG2RAD(30.f))));
            vecRight *= (flLength + (flLength * sin(DEG2RAD(30.f))));
            
            ray.Init(vecCurPos, (vecCurPos + vecLeft));
            pEngineTrace->TraceRay(ray, MASK_SHOT, (CTraceFilter*)&traceFilter, &leftTrace);
            
            ray.Init(vecCurPos, (vecCurPos + vecRight));
            pEngineTrace->TraceRay(ray, MASK_SHOT, (CTraceFilter*)&traceFilter, &rightTrace);
            
            if ((leftTrace.fraction == 1.f) && (rightTrace.fraction != 1.f))
                vecDummy.y -= flCornor; // left
            else if ((leftTrace.fraction != 1.f) && (rightTrace.fraction == 1.f))
                vecDummy.y += flCornor; // right
            
            cmd->viewangles.y = vecDummy.y;
            cmd->viewangles.y -= flWall;
            bRetVal = true;
        }
    }
    return bRetVal;
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


void antiResolverFlip(CUserCmd* cmd, C_BaseEntity* local)
{
    if (!vars.misc.antiaim)
        return;
    
    if (!local || !local->GetAlive())
        return;
    
    if (local->GetMoveType() == MOVETYPE_LADDER || local->GetMoveType() == MOVETYPE_NOCLIP)
        return;
    
    if (cmd->buttons & IN_USE || cmd->buttons & IN_ATTACK)
        return;
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
    if (!vars.misc.antiaim)
        return;
    
    if (!local || !local->GetAlive())
        return;
    
    if (local->GetMoveType() == MOVETYPE_LADDER || local->GetMoveType() == MOVETYPE_NOCLIP)
        return;
    
    if (cmd->buttons & IN_USE || cmd->buttons & IN_ATTACK)
        return;
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
    if (!vars.misc.antiaim)
        return;
    
    if (!local || !local->GetAlive())
        return;
    
    if (local->GetMoveType() == MOVETYPE_LADDER || local->GetMoveType() == MOVETYPE_NOCLIP)
        return;
    
    if (cmd->buttons & IN_USE || cmd->buttons & IN_ATTACK)
        return;
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

void backjizzer(CUserCmd* cmd, C_BaseEntity* local)
{
    if (!vars.misc.antiaim)
        return;
    
    if (!local || !local->GetAlive())
        return;
    
    if (local->GetMoveType() == MOVETYPE_LADDER || local->GetMoveType() == MOVETYPE_NOCLIP)
        return;
    
    if (cmd->buttons & IN_USE || cmd->buttons & IN_ATTACK)
        return;
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
    if (!vars.misc.antiaim)
        return;
    
    if (!local || !local->GetAlive())
        return;
    
    if (local->GetMoveType() == MOVETYPE_LADDER || local->GetMoveType() == MOVETYPE_NOCLIP)
        return;
    
    if (cmd->buttons & IN_USE || cmd->buttons & IN_ATTACK)
        return;
    if(!vars.misc.tank)
        return;
    static bool up = true;
    if (up) cmd->viewangles.x = 70;
    else cmd->viewangles.x = 88;
    up = !up;
}


void lby_spin(CUserCmd* cmd, C_BaseEntity* local)
{
    if (!vars.misc.antiaim)
        return;
    
    if (!local || !local->GetAlive())
        return;
    
    if (local->GetMoveType() == MOVETYPE_LADDER || local->GetMoveType() == MOVETYPE_NOCLIP)
        return;
    
    if (cmd->buttons & IN_USE || cmd->buttons & IN_ATTACK)
        return;
    
    if(!vars.misc.lby_spin)
        return;
    float factor =  360.0 / M_PHI;
    factor = 2; // Change the value of (2) of what ever or take out “factor = 2;”
    cmd->viewangles.y = local->GetLowerBodyYawTarget() +fmodf(pGlobals->curtime * factor, 360.0);
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

void do_real2(CUserCmd* cmd, C_BaseEntity* local){
    
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
    
    if (NextLBYUpdate2(cmd, local)) {
        cmd->viewangles.y += vars.misc.delta;
        //cmd->viewangles.y += 115.f; // less then 180 to prevent 979 animation, but less then 120 so its harder to predict
    }
    
    float factor;
    if(!(local->GetFlags() & FL_ONGROUND)){
        factor =  360.0 / M_PHI;
        factor *= 0.5;
        cmd->viewangles.y = fmodf(pGlobals->curtime * factor, 180.0);
    }
    if(vars.misc.antiaim)
        
        if (pInputSystem->IsButtonDown(KEY_X)){ // Should fuck people up trying to resolve you
            cmd->viewangles.y = rand() % (360 - -360 + 1 ) + -360;
        }
}

void do_fake(CUserCmd* cmd) {
    cmd->viewangles.y = rand() % (180 - -180 + 1 ) + -180;
}

#define TICK_INTERVAL            (pGlobals->interval_per_tick)

void jitter_crooked(CUserCmd* cmd, C_BaseEntity* local)
{
    
    
    float fljit = 78;
    float flCrookedoffset = -20;
    
    if(jitter2)
    {
        cmd->viewangles.y = *local->GetLowerBodyYaw() + flCrookedoffset;
        cmd->viewangles.y += fljit;
    }
    else {
        cmd->viewangles.y = *local->GetLowerBodyYaw() + flCrookedoffset;
        cmd->viewangles.y -= fljit;
    }
}

float get_feet_yaw(C_BaseEntity* local)
{
    if(!local)
        return 0.f;
    
    auto state = local->GetAnimState();
    
    float current_feet_yaw = state->goalFeetYaw;
    
    if(current_feet_yaw >= -360)
        current_feet_yaw = min(current_feet_yaw, 360.f);
    
    return current_feet_yaw;
}

float GetMaxDelta(CCSGOAnimState *animState ) {
    
    float speedFraction = std::max(0.0f, std::min(animState->feetShuffleSpeed, 1.0f));
    
    float speedFactor = std::max(0.0f, std::min(1.0f, animState->feetShuffleSpeed2));
    
    float unk1 = ((animState->runningAccelProgress * -0.30000001) - 0.19999999) * speedFraction;
    float unk2 = unk1 + 1.0f;
    float delta;
    
    if (animState->duckProgress > 0)
    {
        unk2 += ((animState->duckProgress * speedFactor) * (0.5f - unk2));// - 1.f
    }
    
    delta = *(float*)((uintptr_t)animState + 0x3A4) * unk2;
    
    return abs(delta);
}

void LegitAA(CUserCmd* cmd, bool& bSendPacket, C_BaseCombatWeapon* weapon)
{
    if(!vars.misc.legitaa)
        return;
    C_BaseEntity* local = (C_BaseEntity*)pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    if (!cmd || !local || !local->GetAlive() || (cmd->buttons & IN_USE) || (cmd->buttons & IN_ATTACK) || (cmd->buttons & IN_ATTACK2) || local->GetMoveType() == MOVETYPE_LADDER || (weapon->IsSnipScope()))
        return;
    
    static int ChokedTicks = 0;
    static bool Direction = false;
    
    if (pInputSystem->IsButtonDown(KEY_LEFT)) Direction = true;
    if (pInputSystem->IsButtonDown(KEY_RIGHT)) Direction = false;
    
    if (ChokedTicks < 1) {
        bSendPacket = false;
        cmd->viewangles.y += Direction ? 90 : -90;
        
        ChokedTicks++;
    }
    else {
        bSendPacket = true;
        ChokedTicks = 0;
    }
}


void DoAntiaim(CUserCmd* cmd, C_BaseEntity* local, C_BaseCombatWeapon* weapon, bool& bPacket, CCSGOAnimState* animState)
{
    
    if (!vars.misc.antiaim)
        return;
    
    if (!local || !local->GetAlive())
        return;
    
    if (weapon->IsGrenade())
        return;
    
    if (local->GetMoveType() == MOVETYPE_LADDER || local->GetMoveType() == MOVETYPE_NOCLIP)
        return;
    
    if (cmd->buttons & IN_USE || cmd->buttons & IN_ATTACK || (cmd->buttons & IN_ATTACK2 && (*weapon->GetItemDefinitionIndex() == ItemDefinitionIndex::WEAPON_REVOLVER || (CSWeaponType)weapon->GetCSWpnData()->m_WeaponType == CSWeaponType::WEAPONTYPE_KNIFE)))
        return;
    
    if (!vars.misc.fakelag) {
        *bSendPacket = cmd->command_number % 2;
    }
    
    
    
    if(vars.visuals.edge){
        auto bEdge = EdgeAntiAim(local,cmd, 360.f, 45.f);
        
        if (bEdge)
            return;
        
        if(NextLBYUpdate2(cmd, local)){
            cmd->viewangles.y += vars.misc.delta;
        }
    }
    cmd->viewangles.x = 89.f;
    
    static bool fakeswitch = false;
    static bool bFlip = false;
    static bool yFlip = false;
    float maxDelta = GetMaxDelta(animState);
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
        
        
        if(vars.misc.aaX > 0)
        {
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
                if(random < 15) {
                    float change = -70 + (rand() % (int) (140 + 1));
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
            if(vars.misc.aaY == VIEW_ANTIAIM_YAW::Desync1) {
                    cmd->viewangles.y += jitter2 ? get_feet_yaw(local) + 50 : get_feet_yaw(local) - 50;
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
                    cmd->viewangles.y += jitter2 ? get_feet_yaw(local) + 50 : get_feet_yaw(local) - 50;
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
                    
                    cmd->viewangles.y += jitter2 ? get_feet_yaw(local) + 50 : get_feet_yaw(local) - 50;
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
                    cmd->viewangles.y += jitter2 ? get_feet_yaw(local) + 50 : get_feet_yaw(local) - 50;
                }
                if(vars.misc.FaaY == VIEW_ANTIIAIM_FYAW::FakeInverseRotation) {
                    float server_time = local->GetTickBase() * pGlobals->interval_per_tick;
                    
                    if (bSendPacket) {
                        cmd->viewangles.y += (float)(fmod(server_time / 0.80f * 360.0f, 360.0f));
                    } else {
                        cmd->viewangles.y -= (float)(fmod(server_time / 0.80f * 360.0f, 360.0f));
                    }
                }
                if(vars.misc.FaaY == VIEW_ANTIIAIM_FYAW::Desync) {
                    float last_lby = 0.f;
                    float last_lby_time = 0.f;
                    static bool jitter_switch = false;
                    float outgoing_latency = 0.f; //inetchannel
                    float current_lby = local->GetLowerBodyYawTarget();
                    
                    if (current_lby != last_lby || fabs(local->GetVelocity().Length2D()) > 0.1f)
                    {
                        last_lby_time = pGlobals->curtime;
                        last_lby = current_lby;
                    }
                    
                    if (!bSendPacket)
                    {
                        if (fabs(last_lby_time - pGlobals->curtime) > 1.1f - outgoing_latency)
                        {
                            cmd->viewangles.y += 90.f;
                        }
                        else
                        {
                            cmd->viewangles.y += 180.f;
                        }
                    }
                    else
                    {
                        cmd->viewangles.y -= 90.f;
                    }
                    
                    *bSendPacket = jitter_switch;
                    jitter_switch = !jitter_switch;
                    cmd->viewangles.y += jitter2 ? get_feet_yaw(local) + 50 : get_feet_yaw(local) - 50;
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
                    cmd->viewangles.y += jitter2 ? get_feet_yaw(local) + 50 : get_feet_yaw(local) - 50;
                }
                
                if(vars.misc.FaaY == VIEW_ANTIIAIM_FYAW::FakeSideLBY) {
                    int i = 0; i < pEntList->GetHighestEntityIndex(); ++i;
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
}

void AntAimCMove(CUserCmd* cmd){
    if (!vars.misc.antiaim)
        return;
    
    C_BasePlayer* localplayer = (C_BasePlayer*) pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    if (!localplayer || !localplayer->GetAlive())
        return;
    
    C_BaseCombatWeapon* activeWeapon = (C_BaseCombatWeapon*)pEntList->GetClientEntityFromHandle(localplayer->GetActiveWeapon());
    if (!activeWeapon)
        return;
    
    if (cmd->buttons & IN_USE || cmd->buttons & IN_ATTACK || (cmd->buttons & IN_ATTACK2 && *activeWeapon->GetItemDefinitionIndex() == ItemDefinitionIndex::WEAPON_REVOLVER))
        return;
    
    if (localplayer->GetMoveType() == MOVETYPE_LADDER || localplayer->GetMoveType() == MOVETYPE_NOCLIP)
        return;
    
    bool needToFlick = false;
    float tempangle = 0.f;
    static bool lbyBreak = false;
    static float lastCheck;
    static float nextUpdate;
    float vel2D = localplayer->GetVelocity().Length2D();//localplayer->GetAnimState()->verticalVelocity + localplayer->GetAnimState()->horizontalVelocity;
    if (pInputSystem->IsButtonDown(KEY_LEFT) && !manualswitch)
        manualswitch = true;
    
    if (pInputSystem->IsButtonDown(KEY_RIGHT) && manualswitch)
        manualswitch = false;
    
    
    if( vars.misc.lbybreaker ){
        if( CreateMove::sendPacket && (vel2D >= 0.1f || !(localplayer->GetFlags() & FL_ONGROUND) || localplayer->GetFlags() & FL_FROZEN) ){
            // todo: add first choked tick check
            lbyBreak = false;
            lastCheck = pGlobals->curtime;
            nextUpdate = pGlobals->curtime + 0.22;
        } else {
            if( !lbyBreak && ( pGlobals->curtime - lastCheck ) > 0.22 ){
                tempangle = vars.misc.lbybreakermanual ? manualswitch ? 57.5f + vars.misc.lbybreakeroffset : -57.5f + -vars.misc.lbybreakeroffset : vars.misc.lbybreakeroffset;
                lbyBreak = true;
                lastCheck = pGlobals->curtime;
                nextUpdate = pGlobals->curtime + 1.1;
                needToFlick = true;
            } else if( lbyBreak && ( pGlobals->curtime - lastCheck ) > 1.1 ){
                tempangle = vars.misc.lbybreakermanual ? manualswitch ? 57.5f + vars.misc.lbybreakeroffset : -57.5f + -vars.misc.lbybreakeroffset: vars.misc.lbybreakeroffset;
                lbyBreak = true;
                lastCheck = pGlobals->curtime;
                nextUpdate = pGlobals->curtime + 1.1;
                needToFlick = true;
            }
        }
    }
}
