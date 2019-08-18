#include "crosshair.h"
#include "C_BaseEntity.h"

void rCrosshair(C_BaseEntity* local)
{
    if(!vars.visuals.rcrosshair)
        return;
    
    if(!pEngine->IsInGame())
        return;
    
    if(!local)
        return;
    
    static int Height, Width;
    pEngine->GetScreenSize(Width, Height);
    
    int x = Width / 2;
    int y = Height / 2;
    
    Vector punchAngles = local->GetPunchAngles();
    
    int dy = Height / 90;
    int dx = Width / 90;
    int X = x - (dx * punchAngles.y);
    int Y = y + (dy * punchAngles.x);
    
    draw->drawCrosshair(X, Y, Color::White());
}

void DrawScope(C_BaseEntity* local)
{
    if(!vars.misc.noscope || !local || (local && !local->IsScoped()))
        return;
    
    auto weapon = GetActiveWeapon(local);
    
    if(!weapon)
        return;
    if(*weapon->GetItemDefinitionIndex() == WEAPON_AUG || *weapon->GetItemDefinitionIndex() == WEAPON_SG556)
        return;

    
    int w, h;
    pEngine->GetScreenSize(w, h);
    
    draw->drawline(w / 2, 0, w / 2, h, Color::Black());
    draw->drawline(0, h / 2, w, h / 2, Color::Black());
}



void manualaa(C_BaseEntity* Local)
{
    if (!vars.visuals.antiaim_indicator )
        return;
    if(!pEngine->IsInGame() && !pEngine->IsConnected())
        return;
    
    static bool left = false;
    static bool right = false;
    
    static bool switchside = false;
    if (pInputSystem->IsButtonDown(KEY_SLASH))
    {
        switchside = !switchside;
    }
    
    int Height, Width;
    pEngine->GetScreenSize(Height, Width);
    
    int x = Width / 2;
    int y = Height / 2;
    
    if (pInputSystem->IsButtonDown(KEY_LEFT)) {
        left = true; right = false;
    }
    else if (pInputSystem->IsButtonDown(KEY_RIGHT)) {
        left = false; right = true;
    }
    
    //float_t pos = Global::cmd->viewangles.y;
    
    if(vars.visuals.indicatorAA_types == 1){
        
        if( !switchside )
        {
            draw->drawstring(25, 600, Color(255, 0, 0, 255), copyright, ("LEFT"));
        }
        
        if( switchside )
        {
            draw->drawstring(25, 600, Color(255, 0, 0, 255), copyright, ("RIGHT"));
        }
    }
    
    if(vars.visuals.indicatorAA_types == 2){
        
        
        if( !switchside ) {
            draw->drawstring(y + 40, x, Color(255, 0, 0, 125), indicatorFont, ("B")); // Blue
            draw->drawstring(y - 60, x, Color(255, 255, 255, 125), indicatorFont, ("A")); // White
        }
        
        if( switchside ){
            draw->drawstring(y + 40, x, Color(255, 255, 255, 125), indicatorFont, ("B")); // White
            draw->drawstring(y - 60, x, Color(255, 0, 0, 125), indicatorFont, ("A")); // Blue
        }
    }
    
    
}
