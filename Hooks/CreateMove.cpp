#include "main.h"

#include "../Hacks/aimbot.h"
#include "../Hacks/antiaim.h"
#include "../Hacks/autoshoot.h"
#include "../Hacks/bhop.h"
#include "../Hacks/clantag.h"
#include "../Hacks/spammer.h"
#include "../Hacks/fakewalk.h"
#include "../Hacks/LagComp.h"
#include "../Backtrack.hpp"
#include "../moonwalk.hpp"
#include "../Hacks/triggerbot.hpp"
#include "../noduckcooldown.hpp"
#include "../Hacks/EnginePrediction.h"
#include "../Hacks/fakelag.hpp"

Vector tpangles;

void RecoilControl(C_BaseEntity* local, CUserCmd* cmd)
{
    if(!vars.misc.norecoil && !vars.aimbot.rcs)
        return;
    
    Vector punch = local->GetPunchAngles() * 2.f;
    
    if(vars.misc.norecoil)
    {
        if(cmd->buttons & IN_ATTACK)
        {
            
            cmd->viewangles.x -= punch.x;
            cmd->viewangles.y -= punch.y;
        }
        return;
    }
    
    if(vars.aimbot.rcs)
    {
        if(cmd->buttons & IN_ATTACK)
        {
            cmd->viewangles.x -= punch.x * (2.f / 100.f * (vars.aimbot.rcsf / 2));
            cmd->viewangles.y -= punch.y * (2.f / 100.f * (vars.aimbot.rcsf / 2));
        }
        return;
    }
    
}

string GetLocalName()
{
    player_info_t localInfo;
    pEngine->GetPlayerInfo(pEngine->GetLocalPlayer(), &localInfo);
    return localInfo.name;
}


void hacks(CUserCmd* cmd, C_BaseEntity* local, C_BaseCombatWeapon* weapon, Vector& vOldAngles, float& flForwardmove, float& flSidemove,  bool& sendPacket)
{
    
    DoAutoStrafe(cmd, local);
    DoBhop(cmd, local);
    duck->DuckCool(cmd);
    CirlceStrafe(local, cmd, vOldAngles);
    Moonwalk(cmd);
    
    CEnginePrediction::Instance()->Start(cmd);
    DoTrigger(cmd);
    backtracking->legitBackTrack(cmd, local);
    antiResolverFlip(cmd, local);
    turbojizzer(cmd, local);
    backjizzer(cmd, local);
    Freestand(local, cmd);
    lby_spin(cmd, local);
    tank(cmd, local);
    resolverfucker(cmd, local);
    DoAntiaim(cmd, local, weapon, sendPacket);
    DoAim(cmd, local, weapon, flForwardmove, flSidemove);
    ContinuousPistols(cmd, weapon);
    Hitchance(local, weapon);
    AutoCock(cmd, weapon);
    RecoilControl(local, cmd);
    CEnginePrediction::Instance()->End();
    
    DoSpammer();
    Fakewalk(cmd, local);
    //movement->FakeLag(cmd, sendPacket);
    
}

bool bOnce = false;
bool SendPacket = true;
Vector CreateMove::lastTickViewAngles = Vector(0, 0, 0);
bool hkCreateMove(void* thisptr, float flSampleInput, CUserCmd* cmd)
{
    
    misc->clan_tag();
    createmoveVMT->GetOriginalMethod<tCreateMove>(25)(thisptr, flSampleInput, cmd);
    
    if(!cmd->command_number)
        return false;
    
    if(!bSendPacket)
        return false;
    
    auto* local = pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    
    if(!local)
        return false;
    
    if(local->GetLifeState() != 0)
        return false;
    
    if(local->GetHealth() < 1)
        return false;
    
    if(local->GetDormant())
        return false;
    
    if(!bOnce)
    {
        if(draw->m_szCurrentString[2].empty())
        {
            draw->m_szCurrentString[2] = GetLocalName();
        }
        bOnce = true;
    }
    
    C_BaseCombatWeapon* weapon = GetActiveWeapon(local);
    
    if(!weapon)
        return false;
    
    SendPacket = true;
    *bSendPacket = SendPacket;
    
    Vector vOldAngles = cmd->viewangles;
    Vector viewforward, viewright, viewup, aimforward, aimright, aimup;
    Vector qAimAngles;
    
    float forward = cmd->forwardmove;
    float sidemove = cmd->sidemove;
    float upmove = cmd->upmove;
    
    if(pEngine->IsInGame() && pEngine->IsConnected())
    {
        hacks(cmd, local, weapon, vOldAngles, forward, sidemove, *bSendPacket);
        
        if(local->GetAlive()){
            *bSendPacket = true;
        }
        
        if(*bSendPacket)
            tpangles = cmd->viewangles;
        
        FixMovement(vOldAngles, cmd);
        ClampMoves(forward, sidemove, upmove);
        
        if(vars.misc.enabled && vars.misc.antiuntrust)
        {
            cmd->viewangles.ClampAngles();
        }
    }
    Global::cmd = cmd;
    
    *bSendPacket = SendPacket;
    *bSendPacket = true;
    if(cmd && cmd->command_number)
    {
        
        movement->FakeLag(cmd);
        //movement->FakeWalk(cmd);
        
        if(*bSendPacket)
            CreateMove::lastTickViewAngles = cmd->viewangles;
    }
    
    return false;
    
}

