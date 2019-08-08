//
//  autostop.cpp
//  vHook
//
//  Created by Timothy Dillan on 29/7/19.
//  Copyright © 2019 ViKiNG. All rights reserved.
//

#include "autostop.hpp"

void Autostop(CUserCmd* pCmd, C_BaseEntity* pLocal)
{
    if (!vars.aimbot.autostop)
        return;
    
    Vector Velocity = pLocal->GetVelocity();
    static float Speed = 450.f;
    
    Vector Direction;
    Vector RealView;
    VectorAngles(Velocity, Direction);
    pEngine->GetViewAngles(RealView);
    Direction.y = RealView.y - Direction.y;
    
    Vector Forward;
    AngleVectors(Direction, &Forward);
    Vector NegativeDirection = Forward * -Speed;
    
    pCmd->forwardmove = NegativeDirection.x;
    pCmd->sidemove = NegativeDirection.y;
    
    
}
