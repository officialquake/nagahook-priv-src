#include "main.h"

enum LAG
{
    Simple  = 1,
    Adaptive    = 2,
    
};

void Fakelag(CUserCmd* cmd, C_BaseEntity* local);

int Fakelag_AdaptiveFactor()
{
    C_BaseEntity* local_player = (C_BaseEntity*)pEntList->GetClientEntity(pEngine->GetLocalPlayer());
    auto velocity = local_player->GetVelocity();
    
    velocity.z = 0.f;
    
    auto speed = velocity.Length();
    auto distance_per_tick = speed * pGlobals->interval_per_tick;
    int choked_ticks = std::ceilf(64 / distance_per_tick);
    
    return std::min<int>(choked_ticks, 15);
}

