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

static auto percent_col = [](int per) -> Color {
    int red = per < 50 ? 255 : floorf(255 - (per * 2 - 100) * 255.f / 100.f);
    int green = per > 50 ? 255 : floorf((per * 2) * 255.f / 100.f);
    
    return Color(red, green, 0, 255);
};

void DrawFakeAngle(C_BaseEntity* local) {
    
    if(!local)
        return;
    
    if(!local->GetAlive())
        return;
    
    if (vars.misc.antiaim)
        draw->drawstring(10, 25, percent_col(fabs(AntiAem::GFakeAngle.y - AntiAem::GRealAngle.y)), specfont, "FAKE");
}

void manualaa(C_BaseEntity* Local, int keynum)
{
    if (!vars.visuals.antiaim_indicator )
        return;
    if(!vars.misc.manualaa)
        return;
    if(!pEngine->IsInGame() && !pEngine->IsConnected())
        return;
    
    static bool left = false;
    static bool right = false;
    
    
    static bool switchside = false;
    static float resttime;
    //int SwitchSideKey = KEY_SLASH;
    if (pInputSystem->IsButtonDown(KEY_SLASH) && abs(resttime - pGlobals->curtime) > 0.5)
    {
        switchside = !switchside;
        resttime = pGlobals->curtime;
    }
    
    int Height, Width;
    pEngine->GetScreenSize(Height, Width);
    
    int x = Width / 2;
    int y = Height / 2;
    
     //cmd->viewangles.y += (switchside) ? -90 : 90;
    
    left = (switchside) ?  true : false;
    right = (switchside) ? false : true;

    
    /*if(keynum == KEY_SLASH)
    {
        vars.misc.manualcrosshair = !vars.misc.manualcrosshair;
    }*/
    
    //float_t pos = Global::cmd->viewangles.y;
    
    if(vars.visuals.indicatorAA_types == 1){
        
        if( left  )
        {
            draw->drawstring(25, 600, Color(255, 0, 0, 255), copyright, ("LEFT"));
        }
        
        if( right )
        {
            draw->drawstring(25, 600, Color(255, 0, 0, 255), copyright, ("RIGHT"));
        }
    }
    
    if(vars.visuals.indicatorAA_types == 2){
        
        
        if( right  ) {
            draw->drawstring(y + 40, x, Color(255, 0, 0, 125), indicatorFont, ("B")); // Blue
            draw->drawstring(y - 60, x, Color(192, 192, 192, 125), indicatorFont, ("A")); // White
        }
        
        if( left ){
            draw->drawstring(y + 40, x, Color(192, 192, 192, 125), indicatorFont, ("B")); // White
            draw->drawstring(y - 60, x, Color(255, 0, 0, 125), indicatorFont, ("A")); // Blue
        }
    }
    
    
}
