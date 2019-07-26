//
//  menu.cpp
//  macOS base
//

#include "menu.h"
#include "Config.h"

cMenu* menu = new cMenu();
Config cfg;

// Colours

Color nagatoro = Color(255, 0, 0, 255);
Color Red             = Color(255, 0, 57, 255);
Color inactive          = Color(82, 82, 82, 255);
Color MainColor         = Red;

Color FontColor         = Color(255, 255, 255, 250);
Color background        = Color(28, 28, 28, 255);
Color outline           = Color(43, 43, 43, 255);
Color backgroundalpha   = Color(28, 28, 28, 255); // 225 alpha
Color border1           = Color(60, 60, 60, 255);
Color border2           = Color(40, 40, 40, 255);
Color black             = Color(0, 0, 0, 255);
Color Avoz              = Color(163, 12, 224, 255);
Color FontColorDeselect = Color(190, 190, 190, 255);

bool WasPressed, WasReleased;
auto Pressed (ButtonCode_t code) -> void {
    
    if (pInputSystem->IsButtonDown(code)) {
        
        WasPressed = true;
        
    } else if (!(pInputSystem->IsButtonDown(code))) {
        
        if (WasPressed) {
            
            WasReleased = true;
            
        } else {
            
            WasReleased = false;
            
        }
        
        WasPressed = false;
        
    }
    
}

// Menu components

void cMenu::renderCheckbox(int x, int y, const char* str, bool *var) {
    
    int size = 8;
    
    draw->fillrgba(x, y, 18, 8, Color(56,56,56,242));
    draw->fillrgba(x + 1, y + 1, 10 - 2, 8 - 2, Color(252,252,252,255));
    
    if (*var) {
        draw->fillrgba( x, y, 18, 8, Color(124, 200, 0,242));
        draw->fillrgba( x + 9, y + 1, 10 - 1, 8 - 2, Color(252,252,252,255));
    }
    
    if (draw->inArea(x, y, 18, 8)) {
        
        if (*var) {
            draw->fillrgba( x, y, 18, 8, Color(124, 200, 0,242));
            draw->fillrgba( x + 9, y + 1, 10 - 1, 8 - 2, Color(252,252,252,255));
        }
        
        if (WasReleased)
            *var = !*var;
    }
    
    draw->drawbox(x, y, 18, 8, Color(2,2,2,255)); // Outline
    
    draw->drawstring(x + 25, y - 3, FontColor, mFont, str);
    
}


// The sliders are kinda broken, if you click past the ends itll still move
// for ints
void cMenu::renderSlider_c(int x, int y, int w, const char* szString, int& value, int max, int min, Color &col) {
    
    int h = 6;
    int curValue = value * ((float)w / (float)(max));
    
    if (draw->GetMouse().x > x - 4 && draw->GetMouse().y > y - 2 && draw->GetMouse().x < x + w + 4 && draw->GetMouse().y < y + h + 2) {
        
        Color col = Color(40, 45, 55, 255);
        
        if (pInputSystem->IsButtonDown(MOUSE_LEFT)) {
            
            value = (draw->CalcPos(x) / ((float)w / (float)(max)));
            
            if (value > max)
                value = max;
            
            if (value < min)
                value = min;
            
        }
        
    }
    
    // draw->RectOutlined(x, y + 5, w + 2, h, 1, background, Color::Black());
    //  draw->fillrgba(x, y + 5, w + 2, h, Color(40, 45, 55, 255));
    //draw->fillrgba(x, y + 5, curValue, h, Color(40, 45, 55, 255));
    draw->RectOutlined(x + 5, y + 5, w, h, 1, Color(58, 58, 58, 255), Color::Black());
    draw->fillrgba( x + 5, y + 5, curValue, h, col );                       // Color till cursor
    
    draw->drawstring(x + w + 15, y + 3, Color::White(), mFont, to_string(value).c_str());
    draw->drawstring(x + 5, y - 9, FontColor, supremacy, szString);
    //better one
    // draw->fillrgba(x + curValue, y - 1, 4, h + 2, Color(10, 145, 190, 255));
    //  draw->drawbox(x, y, w, h, Color(10, 145, 190, 255));
    //   draw->drawstring(x + curValue - 5, y + 7, FontColor, mFont, to_string(value).c_str());
    
}
void cMenu::renderSlider(int x, int y, int w, const char* szString, int& value, int max, int min) {
    
    int h = 6;
    int curValue = value * ((float)w / (float)(max));
    
    if (draw->GetMouse().x > x - 4 && draw->GetMouse().y > y - 2 && draw->GetMouse().x < x + w + 4 && draw->GetMouse().y < y + h + 2) {
        
        Color col = Color(40, 45, 55, 255);
        
        if (pInputSystem->IsButtonDown(MOUSE_LEFT)) {
            
            value = (draw->CalcPos(x) / ((float)w / (float)(max)));
            
            if (value > max)
                value = max;
            
            if (value < min)
                value = min;
            
        }
        
    }
    
    // draw->RectOutlined(x, y + 5, w + 2, h, 1, background, Color::Black());
    //  draw->fillrgba(x, y + 5, w + 2, h, Color(40, 45, 55, 255));
    //draw->fillrgba(x, y + 5, curValue, h, Color(40, 45, 55, 255));
    draw->RectOutlined(x + 5, y + 5, w, h, 1, Color(58, 58, 58, 255), Color::Black());
    draw->fillrgba( x + 5, y + 5, curValue, h, nagatoro );                       // Color till cursor
    
    draw->drawstring(x + w + 15, y + 3, Color::White(), mFont, to_string(value).c_str());
    draw->drawstring(x + 5, y - 9, FontColor, mFont, szString);
    //better one
    // draw->fillrgba(x + curValue, y - 1, 4, h + 2, Color(10, 145, 190, 255));
    //  draw->drawbox(x, y, w, h, Color(10, 145, 190, 255));
    //   draw->drawstring(x + curValue - 5, y + 7, FontColor, mFont, to_string(value).c_str());
    
}

// for floats
void cMenu::renderSlider(int x, int y, int w, const char* szString, float& value, int max, int min) {
    
    int h = 8;
    int curValue = value * ((float)w / (float)(max));
    
    if (draw->GetMouse().x > x - 4 && draw->GetMouse().y > y - 2 && draw->GetMouse().x < x + w + 4 && draw->GetMouse().y < y + h + 2) {
        
        if (pInputSystem->IsButtonDown(MOUSE_LEFT)) {
            
            value = (draw->CalcPos(x) / ((float)w / (float)(max)));
            
            if (value > max)
                value = max;
            
            if (value < min)
                value = min;
            
        }
        
    }
    /*
     draw->fillrgba(x + curValue, y - 1, 4, h + 2, Color(10, 145, 190, 255));
     draw->drawbox(x, y, w, h, Color(10, 145, 190, 255));
     draw->drawstring(x + curValue - 5, y + 7, FontColor, mFont, to_string(value).c_str());
     */
    char buffer[16];
    
    sprintf(buffer, "%.2f", value);
    
    draw->RectOutlined(x + 5, y + 5, w, h, 1, Color(58, 58, 58, 255), Color(2, 2, 2, 255));
    draw->fillrgba( x + 5, y + 5, curValue, h, nagatoro );                       // Color till cursor
    
    draw->drawstring(x + w + 15, y + 3, Color::White(), mFont, buffer);
    draw->drawstring(x + 5, y - 9, FontColor, mFont, szString);
}




void cMenu::renderCombo(int x, int y, int w, int h, const char* szString, vector<string> szValue, int& currValue, bool* bOpend) {
    
    int Y = y + h;
    
    if(draw->inArea(x, y, w, h)) {
        if(WasReleased) {
            *bOpend = !*bOpend;
        }
    }
    
    if (*bOpend) {
        
        for ( int i = 0; i < szValue.size(); i++ ) {
            
            auto bHover = draw->inArea(x, Y + 2 + ( i * 20 ), w, 18);
            
            draw->RectOutlined(x, Y + 1 + ( i * 20 ), w + 2, 18, 1, bHover ? Color(37, 52, 60, 255) : Color(58, 58, 58, 255), Color(2, 2, 2, 255));
            draw->drawstring(x + 5, Y + 2 + (i*20), Color::White(), mFont, szValue[i].c_str());
            
            if (draw->inArea(x, Y + 2 + ( i * 20 ), w, 18)) {
                if(WasPressed){
                    currValue = i;
                    *bOpend = false;
                }
            }
        }
    }
    
    if(currValue == 0)
        szString = szString;
    else
        szString = szValue[currValue].c_str();
    
    // Draws the box
    draw->RectOutlined(x, y, w + 2, h, 1, Color(58, 58, 58, 255), Color(2, 2, 2, 255));
    ;
    draw->drawstring(x + 5, y + (h/2) - 7, FontColor, mFont, szString);
    
    
    if (!*bOpend)
    {
        // draw arrow pointing down
        draw->fillrgba( ( x + w - h + 113 - 107 ), ( y + 8 ), 1, 1, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 114 - 107 ), ( y + 8 ), 1, 2, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 115 - 107 ), ( y + 8 ), 1, 3, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 116 - 107 ), ( y + 8 ), 1, 4, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 117 - 107 ), ( y + 8 ), 1, 3, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 118 - 107 ), ( y + 8 ), 1, 2, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 119 - 107 ), ( y + 8 ), 1, 1, Color( 255, 255, 255, 255 ) );
    }
    else
    {
        // draw arrow pointing up
        draw->fillrgba( ( x + w - h + 113 - 107 ), ( y + 11 ), 1, 1, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 114 - 107 ), ( y + 10 ), 1, 2, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 115 - 107 ), ( y + 9 ), 1, 3, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 116 - 107 ), ( y + 8 ), 1, 4, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 117 - 107 ), ( y + 9 ), 1, 3, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 118 - 107 ), ( y + 10 ), 1, 2, Color( 255, 255, 255, 255 ) );
        draw->fillrgba( ( x + w - h + 119 - 107 ), ( y + 11 ), 1, 1, Color( 255, 255, 255, 255 ) );
    }
}

void cMenu::renderButton(int x, int y, const char* szString, bool* var) {
    
    int w = 60;
    int h = 20;
    
    if(draw->inArea(x, y, w, h)) {
        if(WasPressed) {
            *var = true;
        }
    } else {
        *var = false;
    }
    
    bool bHovering = draw->inArea(x, y, w, h);
    draw->drawgradient(x, y, w, h, bHovering ? Color(37, 52, 60, 255) : Color(25, 25, 25, 255), Color(25, 25, 25, 255));
    draw->drawbox(x + 1, y + 1, w - 2, h - 2, bHovering ? Color(64, 91, 106, 255) : Color(67, 67, 67, 255));
    draw->drawbox(x, y, w, h, bHovering ? Color(25, 35, 40, 255) : Color(9, 9, 9, 255));
    
    draw->drawstring(x + w / 2, y + h / 2, FontColor, framefont, szString, true);
    
}

void cMenu::playerbutton(int x, int y, int w, int h, int index, int& playercount, const char* szString)
{
    y += index * 24;
    
    if(draw->inArea(x, y, w, h))
    {
        if(WasReleased)
        {
            playercount = index;
        }
    }
    
    bool bHovering = draw->inArea(x, y, w, h);
    draw->drawgradient(x, y, w, h, bHovering ? Color(30, 30, 30, 255), FontColor : Color(15, 15, 15, 255), Color(15, 15, 15, 255));
    draw->drawbox(x, y, w, h, Color::Black());
    draw->drawstring(x + w / 2, y + h / 2, FontColor, mFont, szString, true);
}

void cMenu::render_section(int x, int y, int w, int h, const char* label)
{
    
    draw->RectOutlined(x, y, w, h, 1, Color(28, 28, 28, 255), Color(43, 43, 43, 255));
    // ImGui::PushFont(Fonts::section);
    
    auto text_size = draw->GetTextSize(label, mSection);
    
    draw->fillrgba(x + 12, y - 1, text_size.x + 7, 3, Color(28, 28, 28, 255));
    // draw->drawbox(x + 12, y - 1, text_size.x + 7, 3, Color(255, 20, 20, 255));
    draw->drawstring(x + 15, y - 6, FontColor, mSection, label);
}

void cMenu::render_tab_section(int x, int y, int w, int h)
{
    draw->RectOutlined(x, y, w, h, 1, Color(28, 28, 28, 255), Color(43, 43, 43, 255));
}

// Made by ViKiNG
void cMenu::drawcolorpicker(int x, int y, const char *szString, Color &col) {
    
    int oner = 6;
    float flRnbw = 0.0005f;
    int currPosX, currPosY;
    
    for(int i = 0 ; i < 21; i++) {
        flRnbw += 0.045f;
        
        Color col1 = Color::GetFromHSB(flRnbw, 1.0f, 1.0f);
        Color col2 = Color::GetFromHSB(flRnbw, 0.90f, 0.90f);
        Color col3 = Color::GetFromHSB(flRnbw, 0.80f, 0.80f);
        Color col4 = Color::GetFromHSB(flRnbw, 0.70f, 0.70f);
        Color col5 = Color::GetFromHSB(flRnbw, 0.60f, 0.60f);
        Color col6 = Color::GetFromHSB(flRnbw, 0.50f, 0.50f);
        Color col7 = Color::GetFromHSB(flRnbw, 0.40f, 0.40f);
        Color col8 = Color::GetFromHSB(flRnbw, 0.30f, 0.30f);
        Color col9 = Color::GetFromHSB(flRnbw, 0.20f, 0.20f);
        Color col10 = Color::GetFromHSB(flRnbw, 0.15f, 0.15f);
        Color col11 = Color::GetFromHSB(flRnbw, 0.10f, 0.10f);
        
        draw->fillrgba(x + i * oner, y, oner, oner, Color(col1.r(), col1.g(), col1.b(), 255));
        draw->fillrgba(x + i * oner, y + oner * 1, oner, oner, Color(col2.r(), col2.g(), col2.b(), 255));
        draw->fillrgba(x + i * oner, y + oner * 2, oner, oner, Color(col3.r(), col3.g(), col3.b(), 255));
        draw->fillrgba(x + i * oner, y + oner * 3, oner, oner, Color(col4.r(), col4.g(), col4.b(), 255));
        draw->fillrgba(x + i * oner, y + oner * 4, oner, oner, Color(col5.r(), col5.g(), col5.b(), 255));
        draw->fillrgba(x + i * oner, y + oner * 5, oner, oner, Color(col6.r(), col6.g(), col6.b(), 255));
        draw->fillrgba(x + i * oner, y + oner * 6, oner, oner, Color(col7.r(), col7.g(), col7.b(), 255));
        draw->fillrgba(x + i * oner, y + oner * 7, oner, oner, Color(col8.r(), col8.g(), col8.b(), 255));
        draw->fillrgba(x + i * oner, y + oner * 8, oner, oner, Color(col9.r(), col9.g(), col9.b(), 255));
        draw->fillrgba(x + i * oner, y + oner * 9, oner, oner, Color(col10.r(), col10.g(), col10.b(), 255));
        draw->fillrgba(x + i * oner, y + oner * 10, oner, oner, Color(col11.r(), col11.g(), col11.b(), 255));
        
        int x1 = x + i * oner;
        int y2 = y + oner * 1;
        int y3 = y + oner * 2;
        int y4 = y + oner * 3;
        int y5 = y + oner * 4;
        int y6 = y + oner * 5;
        int y7 = y + oner * 6;
        int y8 = y + oner * 7;
        int y9 = y + oner * 8;
        int y10 = y + oner * 9;
        int y11 = y + oner * 10;
        
        if(draw->inArea(x1, y, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col1;
                draw->drawbox(x1, y, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y;
            }
        } else if(draw->inArea(x1, y2, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col2;
                draw->drawbox(x1, y2, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y2;
            }
        } else if(draw->inArea(x1, y3, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col3;
                draw->drawbox(x1, y3, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y3;
            }
        } else if(draw->inArea(x1, y4, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col4;
                draw->drawbox(x1, y4, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y4;
            }
        } else if(draw->inArea(x1, y5, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col5;
                draw->drawbox(x1, y5, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y5;
            }
        } else if(draw->inArea(x1, y6, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col6;
                draw->drawbox(x1, y6, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y6;
            }
        }
        else if(draw->inArea(x1, y7, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col7;
                draw->drawbox(x1, y7, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y7;
            }
        }
        else if(draw->inArea(x1, y8, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col8;
                draw->drawbox(x1, y8, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y8;
            }
        }
        else if(draw->inArea(x1, y9, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col9;
                draw->drawbox(x1, y9, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y9;
            }
        }
        else if(draw->inArea(x1, y10, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col10;
                draw->drawbox(x1, y10, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y10;
            }
        }
        else if(draw->inArea(x1, y11, oner, oner)) {
            if(pInputSystem->IsButtonDown(MOUSE_LEFT)) {
                col = col11;
                draw->drawbox(x1, y11, oner, oner, Color::Black());
                currPosX = x1;
                currPosY = y11;
            }
        }
    }
    
    draw->fillrgba(x, y + 73, 5, 20, Color(col.r(), col.g(), col.b(), 255));
    draw->drawbox(x, y + 73, 5, 20, Color::Black());
    
    string strPalette;
    
    strPalette.append("R: ");
    strPalette.append(to_string(col.r()));
    
    strPalette.append(" G: ");
    strPalette.append(to_string(col.g()));
    
    strPalette.append(" B: ");
    strPalette.append(to_string(col.b()));
    
    draw->drawstring(x, y - 20, Color::White(), mFont, szString);
    draw->drawstring(x + 10, y + 78, Color::White(), mFont, strPalette.c_str());
}

// Tabs

void cMenu::renderAim(int x, int y) {
    
    this->renderCheckbox(x - 15, y, "Enabled", &vars.aimbot.enabled);
    this->renderCheckbox(x - 15, y + 20, "SilentAim", &vars.aimbot.silent);
    //draw->drawstring(x + 5, y + 40, FontColor, mFont, "FOV");
    this->renderSlider(x + 5, y + 40, 150, "Fov", vars.aimbot.FovToPlayer, 180, 0);
    // draw->drawstring(x, y + 70, FontColor, mFont, "Hitbox");
    this->renderSlider(x + 5, y + 70, 150, "Hitbox", vars.aimbot.hitbox, 19, 0);
    this->renderCheckbox(x - 15, y + 90, "Auto Wall", &vars.aimbot.autowall);
    this->renderSlider(x + 5, y + 110, 150, "Minimum Damage", vars.aimbot.mindmg, 100, 0);
    this->renderCheckbox(x - 15, y + 140, "Hitchance", &vars.aimbot.hitchance);
    this->renderSlider(x + 5, y + 155, 150, "", vars.aimbot.accuracyhithcance, 100, 0);
    this->renderSlider(x + 5, y + 180, 150, "Pointscale", vars.aimbot.pointscale, 100, 0);
    
    vector<string> Resolve;  // Resolver
    
    
    Resolve.push_back("Experimental");
    Resolve.push_back("LBYResolver");
    Resolve.push_back("Smart");
    Resolve.push_back("Evolution");
    Resolve.push_back("Test");
    Resolve.push_back("Synp1");
    Resolve.push_back("Synp2");
    
    
    this->renderCheckbox(x - 15, y + 200, "Yaw Resolver", &vars.aimbot.Yawresolver);
    this->renderCombo(x + 5, y + 220, 110, 20, "Off", Resolve, vars.aimbot.yresolve, &vars.resolver_opend); // 150
    this->renderCheckbox(x - 15, y + 245, "Baim Under x HP", &vars.aimbot.baimhp);
    this->renderSlider(x - 5, y + 260, 150, "", vars.aimbot.baimxhp, 100, 0);
    
    //Middle
    this->renderCheckbox(x + 235, y, "Auto Scope", &vars.aimbot.autoscope);
    this->renderCheckbox(x + 235, y + 20, "Auto Pistol", &vars.aimbot.autopistol);
    this->renderCheckbox(x + 235, y + 40, "Auto Crouch", &vars.aimbot.autocrouch);
    this->renderCheckbox(x + 235, y + 60, "Auto Shoot", &vars.aimbot.autoshoot);
    this->renderCheckbox(x + 235, y + 80, "Backtrack", &vars.aimbot.backtrack);
    this->renderCheckbox(x + 235, y + 100, "Hitscan", &vars.aimbot.hitscan);
    this->renderCheckbox(x + 235, y + 150, "Triggerbot", &vars.aimbot.trigger);
    this->renderCheckbox(x + 235, y + 240, "Radar", &vars.misc.radar);
    //this->renderCheckbox(x + 235, y + 260, "Auto Cock", &vars.aimbot.autocock);

    this->renderSlider(x + 230, y + 180, 150, "Player Chams", vars.visuals.playerchams_alpha, 255, 0);
    this->renderSlider(x + 230, y + 200, 150, "Hand Chams", vars.visuals.handchams_alpha, 255, 0);
    this->renderSlider(x + 230, y + 220, 150, "Weapon Chams", vars.visuals.weaponchams_alpha, 255, 0);
    //this->renderCheckbox(x + 235, y + 280, "Auto Stop", &vars.aimbot.autostop);
    
    
    vector<string> hitscan;
    // X
    hitscan.push_back("off");
    hitscan.push_back("low");//xanax moving
    hitscan.push_back("normal");//supremacy $
    hitscan.push_back("high");//gamesense
    hitscan.push_back("extreme");
    hitscan.push_back("baim");
    /*CT.push_back("Test 2");
     CT.push_back("Mixed");*/
    this->renderCombo(x + 260, y + 120, 150, 20, "Hitscan", hitscan, vars.aimbot.hitscantype, &vars.hitscan_opend);
    
    
    
    
    
    
}

void cMenu::renderAntiAim(int x, int y) {
    
    vector<string> Pitch;  // Real Pitch
    vector<string> Yaw;  // Real Yaw
    vector<string> FakeYaw; // Fake Yaw
    vector<string> MY; // Ground Yaw
    vector<string> AY; // Air Yaw
    // Pitch
    Pitch.push_back("Off");
    Pitch.push_back("Down");
    Pitch.push_back("Up");
    // Yaw
    Yaw.push_back("Off");
    Yaw.push_back("Backwards");
    Yaw.push_back("Jitter");
    Yaw.push_back("FakeStatic");
    Yaw.push_back("FJitter");
    Yaw.push_back("SlowSpin");
    Yaw.push_back("FastSpin");
    Yaw.push_back("RandomBackJitter");
    Yaw.push_back("BackJitter");
    Yaw.push_back("LowerYaw");
    Yaw.push_back("SidewaysLeft");
    Yaw.push_back("SidewaysRight");
    Yaw.push_back("LBYBreaker");
    // Fake Yaw
    // Fake Yaw
    FakeYaw.push_back("Off");
    FakeYaw.push_back("FakeSpin");
    FakeYaw.push_back("FakeLBYHook");
    FakeYaw.push_back("FakeTwoStep");
    FakeYaw.push_back("FakeLowerBody135");
    FakeYaw.push_back("FakeInverseRotation");
    FakeYaw.push_back("FakeJitter");
    FakeYaw.push_back("FakeLBY");
    FakeYaw.push_back("FakeSideLBY");
    //Moving Yaw
    MY.push_back("Off");
    MY.push_back("LowerYaw");
    MY.push_back("Backwards Jitter");
    MY.push_back("Rotate");
    // Air Yaw
    AY.push_back("Off");
    AY.push_back("Rotate");
    
    this->renderCheckbox(x - 15, y, "Anti-Aim", &vars.misc.antiaim);
    this->renderCheckbox(x - 15, y + 20, "Show Real Angles", &vars.misc.thirdpersonmode);
    
    //this->renderSlider(x - 5, y + 60, 150, "LBY Delta", vars.misc.delta, 180, 0);
    this->renderCheckbox(x - 15, y + 40, "AA Turbo Jitter", &vars.misc.turbojizzer);
    this->renderCheckbox(x - 15, y + 60, "AA Back Jitter", &vars.misc.backjizzer);
    this->renderCheckbox(x - 15, y + 80, "AA LBY Spin", &vars.misc.lby_spin);
    this->renderCheckbox(x - 15, y + 100, "AA Tank", &vars.misc.tank);
    this->renderCheckbox(x - 15, y + 120, "Resolver Fucker", &vars.misc.resolverfucker);
    this->renderCheckbox(x - 15, y + 140, "Anti Resolver Flip", &vars.misc.antiResolverFlip);
    //this->renderCheckbox(x - 15, y + 180, "Dlights", &vars.misc.dlights);
    this->renderCheckbox(x - 15, y + 160, "Freestand", &vars.aimbot.freestand);
    if (!vars.freestand_opend) {
        
        this->renderSlider(x - 5, y + 180, 150, "Jitter", vars.aimbot.jitter, 180, 0);
        
    }
    this->renderCheckbox(x - 15, y + 200, "Fake", &vars.misc.fakeaa); // 60
    this->renderCombo(x - 15, y + 240, 90, 20, "Pitch", Pitch, vars.misc.aaX, &vars.aaX_opend);
    if(!vars.aaX_opend){
        this->renderCombo(x - 15, y + 270, 90, 20, "Yaw", Yaw, vars.misc.aaY, &vars.aaY_opend);
    }
    if((!vars.aaX_opend) && !vars.aaY_opend) {
        this->renderCombo(x - 15, y + 300, 90, 20, "fYaw", FakeYaw, vars.misc.FaaY, &vars.FaaY_opend);
    }
}
/*
 this->renderCombo(x + 300, y + 60, 125, 20, "Pitch", X, vars.misc.aaX, &vars.aaX_opend); // 80
 if(!vars.aaX_opend)
 
 this->renderCombo(x + 300, y + 80, 125, 20, "Yaw", Y, vars.misc.aaY, &vars.aaY_opend);
 if((!vars.aaX_opend) && !vars.aaY_opend)
 
 this->renderCombo(x + 300, y + 100, 125, 20, "Fake Yaw", FY, vars.misc.FaaY, &vars.FaaY_opend); // 100*/
//if((!vars.aaX_opend) && !vars.aaY_opend && !vars.FaaY_opend)

//this->renderCombo(x + 300, y + 120, 125, 20, "Moving Yaw", MY, vars.misc.MaaY, &vars.MaaY_opend); // 120
//if((!vars.aaX_opend) && !vars.aaY_opend && !vars.FaaY_opend && !vars.misc.MaaY)

//this->renderCombo(x + 300, y + 140, 125, 20, "Air Yaw", AY, vars.misc.AaaY, &vars.AaaY_opend); // 140


/*void cMenu::renderPlayer(int x, int y)
 {
 vector<string> conf;
 
 conf.push_back("HvH");
 conf.push_back("HvH 2");
 conf.push_back("HvH 3");
 
 this->renderCombo(x + 15, y + 153,  125, 20, "HvH", conf, cfg.cfgcombo, &vars.cfg_opend);
 if(!vars.cfg_opend) {
 this->renderButton(x + 19, y + 173, "Save", &cfg.saveconfig);
 this->renderButton(x + 80, y + 173, "Load", &cfg.loadconfig);
 }
 
 }
 }*/


void cMenu::renderPlayer(int x, int y) {
    
    this->renderCheckbox(x - 15, y, "Enabled", &vars.visuals.enabled);
    this->renderCheckbox(x, y + 20, "Enemy only", &vars.visuals.enemyonly);
    this->renderCheckbox(x, y + 40, "Vis Only", &vars.visuals.visonly);
    this->renderCheckbox(x, y + 60, "Box", &vars.visuals.box);
    this->renderCheckbox(x, y + 80, "Name", &vars.visuals.name);
    this->renderCheckbox(x, y + 100, "Health", &vars.visuals.health);
    this->renderCheckbox(x, y + 120, "Armour", &vars.visuals.armour);
    this->renderCheckbox(x, y + 140, "Heath text", &vars.visuals.healthtext);
    this->renderCheckbox(x, y + 160, "Skeleton", &vars.visuals.skeleton);
    this->renderCheckbox(x, y + 180, "Snaplines", &vars.visuals.snapline);
    this->renderCheckbox(x, y + 200, "Grenade ESP", &vars.visuals.grenade);
    this->renderCheckbox(x, y + 220, "Weapon ESP", &vars.visuals.active);
    
    vector<string> Players;
    vector<string> Hands;
    vector<string> Weapons;
    
    Players.push_back("Platinum");
    Players.push_back("Texture");
    Players.push_back("WireFrame");
    Players.push_back("Crystal Blue");
    Players.push_back("Mexican Cartel");
    Players.push_back("Random2");
    Players.push_back("Glass");
    Players.push_back("Wildfire");
    Players.push_back("Random4");
    Players.push_back("Random5");
    Players.push_back("Random6");
    Players.push_back("Plastic");
    Hands.push_back("Platinum");
    Hands.push_back("Texture");
    Hands.push_back("Wireframe");
    Hands.push_back("Crystal Blue");
    Hands.push_back("Mexican Cartel");
    Hands.push_back("Random2");
    Hands.push_back("Glass");
    Hands.push_back("Wildfire");
    Hands.push_back("Random4");
    Hands.push_back("Random5");
    Hands.push_back("Random6");
    Hands.push_back("Plastic");
    Weapons.push_back("Platinum");
    Weapons.push_back("Texture");
    Weapons.push_back("Wireframe");
    Weapons.push_back("Crystal Blue");
    Weapons.push_back("Mexican Cartel");
    Weapons.push_back("Random2");
    Weapons.push_back("Glass");
    Weapons.push_back("Wildfire");
    Weapons.push_back("Random4");
    Weapons.push_back("Random5");
    Weapons.push_back("Random6");
    Weapons.push_back("Plastic");
    
    this->renderCheckbox(x, y + 240, "Player Chams", &vars.visuals.chams);
    this->renderCheckbox(x, y + 260, "Hand Chams", &vars.visuals.handchams);
    this->renderCheckbox(x, y + 280, "Weapon Chams", &vars.visuals.weaponchams);
    if(vars.visuals.chams) {
        this->renderCombo(x + 10, y + 300, 150, 20, "Platinum", Players, vars.visuals.playersType, &vars.players_opend);
    }
    if(vars.visuals.handchams) {
        if(!vars.players_opend)
            this->renderCombo(x + 10, y + 320, 150, 20, "Platinum", Hands, vars.visuals.handsType, &vars.hands_opend);
    }
    if(vars.visuals.weaponchams) {
        if((!vars.players_opend) && !vars.hands_opend)
            this->renderCombo(x + 10, y + 340, 150, 20, "Platinum", Weapons, vars.visuals.weaponType, &vars.weapons_opend);
    }
    
    int iScreenWidth, iScreenHeight;
    pEngine->GetScreenSize(iScreenWidth, iScreenHeight);
    
    //Middle
    this->renderCheckbox(x + 235, y, "SkinChanger", & vars.visuals.skinc);
    this->renderCheckbox(x + 235, y + 20, "Dropped Weapons", & vars.visuals.weapons);
    this->renderCheckbox(x + 235, y + 40, "Bomb Timer", & vars.visuals.bombtimer);
    this->renderCheckbox(x + 235, y + 60, "Defusing", & vars.visuals.defusing);
    this->renderCheckbox(x + 235, y + 80, "Rescuing", & vars.visuals.rescuing);
    this->renderCheckbox(x + 235, y + 100, "Scoping", & vars.visuals.scoped);
    this->renderCheckbox(x + 235, y + 120, "No Flash", & vars.misc.noflash);
    this->renderSlider(x + 230, y + 140, 150, "", vars.misc.flashalpha, 255, 0);
    this->renderCheckbox(x + 235, y + 160, "Recoil Crosshair", & vars.visuals.rcrosshair);
    this->renderCheckbox(x + 235, y + 240, "No Scope", & vars.misc.noscope);
    //this->renderCheckbox(x + 235, y + 220, "Radar", & vars.misc.radar);
    
    this->renderCheckbox(x + 235, y + 180, "AA Indicators", & vars.visuals.antiaim_indicator);
    std::vector<std::string> Indicator;
    
    Indicator.push_back("Off");
    Indicator.push_back("Words");
    Indicator.push_back("Arrows");
    
    this->renderCombo(x + 235, y + 200, 125, 20, "Lit", Indicator, vars.visuals.indicatorAA_types, &vars.indicatorAA_opend);
    this->renderCheckbox(x + 235, y + 260, "AA Lines", & vars.visuals.aaline);
    this->renderCheckbox(x + 235, y + 280, "Angle Line Names", & vars.visuals.anglelinenames);
    //this->renderCheckbox(x + 235, y + 280, "Hitmarkers", &vars.visuals.hitmarker);
    //this->renderCheckbox(x + 235, y + 300, "Enemies Hitmarkers", &vars.visuals.enemyhit);
    //this->renderCheckbox(x + 235, y + 320, "Allies Hitmarkers", &vars.visuals.allieshit);
    //this->renderSlider(x + 230, y + 280, 150, "M4A4 Skin", vars.visuals.m4a4skin, 3000, 0);
    //this->renderSlider(x + 230, y + 360, 150, "Hit Size", vars.visuals.hitsize, 32, 0);
    //this->renderSlider(x + 230, y + 380, 150, "Hit Gap", vars.visuals.hitinnergap, 16, 0);*/
    //this->renderCheckbox(x + 150, y + 195, "nightmode(wip)", & vars.misc.nightmode); (wip)
    
    
    // Left side
    
    
}


void cMenu::renderMisc(int x, int y) {
    
    vector<string> CT;
    // X
    CT.push_back("off");
    CT.push_back("xanax");//xanax moving
    CT.push_back("supremacy");//supremacy $
    CT.push_back("gamesense");//gamesense
    CT.push_back("zeus");
    /* CT.push_back("Test");
     CT.push_back("Test 2");
     CT.push_back("Mixed");*/
    
    this->renderCheckbox(x, y, "Bhop", &vars.misc.bhop);
    this->renderCheckbox(x, y + 20, "Auto strafe", &vars.misc.autostrafe);
    this->renderCheckbox(x, y + 40, "Circle Strafe", &vars.misc.cstrafe);
    this->renderCheckbox(x, y + 60, "FOV Changer", &vars.misc.fovt);
    this->renderSlider(x - 5, y + 80, 150, "", vars.misc.fov, 70, 0);
    this->renderCheckbox(x, y + 100, "No recoil", &vars.misc.norecoil);
    this->renderCheckbox(x, y + 120, "No visual recoil", &vars.misc.novisual);
    this->renderCheckbox(x, y + 140, "Chat Spam", &vars.misc.spammer);
    //clan tags
    //this->renderCheckbox(x, y + 150, "Clan Tag", &vars.misc.vangeme);
    //this->renderCheckbox(x, y + 150, "skeet.cc", &vars.misc.gamesense);
    //this->renderCheckbox(x, y + 170, "aimware.net", &vars.misc.aimware);
    // this->renderCheckbox(x, y + 145, "Clantag", &vars.misc.clantag);
    this->renderCheckbox(x, y + 160, "Thirdperson", &vars.misc.thirdperson);
    this->renderSlider(x - 5, y + 180, 150, "", vars.misc.tpoffset, 200, 0);
    this->renderCheckbox(x, y + 200, "Moonwalk", &vars.misc.moonwalk);
    this->renderCheckbox(x, y + 220, "Watermark", &vars.misc.watermark);
    
    
    // Fake Lag
    this->renderCheckbox(x + 235, y, "WorldPaint", &vars.misc.worldpaint);
    this->renderCheckbox(x + 235, y + 20, "Spec List", &vars.misc.showspectators);
    this->renderCheckbox(x + 235, y + 40, "Antiscreenshot", &vars.misc.antiscreenshot);
    this->renderCheckbox(x + 235, y + 60, "Anti untrust", &vars.misc.antiuntrust);
    this->renderCheckbox(x + 235, y + 80, "Asuswall", &vars.misc.asuswalls);
    this->renderSlider(x + 235, y + 100, 150, "", vars.misc.asusalpha, 1.f, 0.f);
    
    this->renderCheckbox(x + 235, y + 120, "No Smoke", &vars.visuals.nosmoke);
    this->renderCheckbox(x + 235, y + 140, "No Duck Cool", &vars.misc.noduckcooldown);
    this->renderCheckbox(x + 235, y + 160, "Spread Crosshair", &vars.misc.spreadcrosshair);
    /*this->renderCheckbox(x + 235, y + 180, "Fake Lag (no worc)", &vars.misc.fakelag);
     this->renderCheckbox(x + 235, y + 200, "Adaptive", &vars.misc.adaptive);
     
     if(!vars.fakelag_opend)
     this->renderSlider(x + 235, y + 220, 150, "Fake Lag Factor", vars.misc.fakelagfactor, 9, 0);*/
    
    
    vector<string> conf;
    
    conf.push_back("scout");
    conf.push_back("autos");
    conf.push_back("legit");
    conf.push_back("rage");
    conf.push_back("rifles");
    
    this->renderCombo(x, y + 245,  150, 20, "scout", conf, cfg.cfgcombo, &vars.cfg_opend);
    if(!vars.cfg_opend) {
        this->renderButton(x, y + 265, "Save", &cfg.saveconfig);
        this->renderButton(x + 85, y + 265, "Load", &cfg.loadconfig);
    }
    
}

void cMenu::renderColors(int x, int y) {
    
    vector<string> Colors;
    
    Colors.push_back("CT Colours");
    Colors.push_back("T Colours");
    Colors.push_back("Hand/Weapon Colours");
    Colors.push_back("World Colours");
    Colors.push_back("Hitmarker Colours");
    
    
    
    this->renderCombo(x, y + 300 + 14, 125, 20, "CT Colours", Colors, vars.colors.combo, &vars.colors_opend);
    
    if(vars.colors.combo == 0) {
        this->drawcolorpicker(x, y + 22, "CT Box", vars.colors.ctbox);
        this->drawcolorpicker(x, y + 150, "CT BoxIgn", vars.colors.ctbox_ign);
        this->drawcolorpicker(x + 235, y + 22, "CT Chams", vars.colors.ctchams);
        this->drawcolorpicker(x + 235, y + 150, "CT ChamIgn", vars.colors.ctchams_ign);
    }
    if(vars.colors.combo == 1) {
        this->drawcolorpicker(x, y + 22, "T Box", vars.colors.tbox);
        this->drawcolorpicker(x, y + 150, "T BoxIgn", vars.colors.tbox_ign);
        this->drawcolorpicker(x + 235, y + 22, "T Chams", vars.colors.tchams);
        this->drawcolorpicker(x + 235, y + 150, "T ChamIgn", vars.colors.tchams_ign);
    }
    if(vars.colors.combo == 2) {
        this->drawcolorpicker(x, y + 22, "Hands", vars.colors.hands);
        this->drawcolorpicker(x + 235, y + 20, "Weapon", vars.colors.weapon);
    }
    if(vars.colors.combo == 3) {
        this->drawcolorpicker(x, y + 22, "World", vars.colors.world);
        this->drawcolorpicker(x + 235, y + 20, "Sky", vars.colors.sky);
    }
    if(vars.colors.combo == 4) {
        this->drawcolorpicker(x, y + 22, "Hitmarker", vars.colors.hitmarkers);

    }
    
    
    
    
    
}

// Menu tabs
enum mTab
{
    Main     = 0,
    tab_1    = 1,//rage
    tab_2    = 2,//aa
    tab_3    = 3,//legit
    tab_4    = 4,//visuals
    tab_5    = 5,//visuals
};

static int curTab = mTab::Main;

// This is where the menu is "put together"
void cMenu::renderMenu() {
    
    static int x = 100;
    static int y = 100;
    int w = 489;
    int h = 500;
    int hh = 22; // The height of the dragable area
    
    
    
    draw->fillrgba(x, y, w, h, Color(28, 28, 28, 255));
    draw->fillrgba(x, y + 19, w, 3, Color(255, 0, 0, 255));
    draw->drawstring(x + ( ( w - 4 ) / 2 ) + 2, y + 10, Color::White(), mFont, "-Nagahook", true);
    
    // Draws tabs
    if(curTab != 0){
        
        draw->drawline(x + 5, y + h - 10, x + 15, y + h - 13, FontColor);
        draw->drawline(x + 5, y + h - 10, x + 15, y + h - 7, FontColor);
        
        draw->drawline(x + 5, y + h - 10, x + 25, y + h - 10, FontColor);
        
        //draw->drawline(x + 15, y + h - 10, x + 15, y + h - 4, FontColor);
        
        if(draw->inArea(x - 5, y + h - 30, 30, 50)) {
            
            
            
            if(WasReleased)
                
                curTab = 0;
            
            
        }
        
        
        
        //draw->drawstring(x + 5, y + h - 13, FontColor, mFont, "back");
    }
    // Handles tabs
    
    //top
    
    if(curTab == 0){
        
        if(draw->inArea(x + 15, y + 37, 143, 200)) {
            
            
            
            if(WasReleased)
                
                curTab = 1;
            
            
        } else if(draw->inArea(x + 173, y + 37, 143, 200)) {
            
            
            
            if(WasReleased)
                
                curTab = 2;
            
            
        } else if(draw->inArea(x + 331, y + 37, 143, 200)) {
            
            
            
            if(WasReleased)
                
                curTab = 3;
            
        }
        
        //bottom
        
        else if(draw->inArea(x + 15, y + 262, 143, 200)) {
            
            
            if(WasReleased)
                
                curTab = 4;
            
        } else if(draw->inArea(x + 173, y + 262, 143, 200)) {
            
            
            if(WasReleased)
                
                curTab = 5;
            
        }
    }
    
    switch (curTab) {
            
        case 0:
            //top
            
            this->render_tab_section(x + 15, y + 37, 143, 200);
            draw->drawstring(x + 85, y + 135, nagatoro, osFont, "B", true);
            
            this->render_tab_section(x + 173, y + 37, 143, 200);
            draw->drawstring(x + 243, y + 135, nagatoro, osFont, "A", true);
            
            this->render_tab_section(x + 331, y + 37, 143, 200);
            draw->drawstring(x + 401, y + 135, nagatoro, osFont, "F", true);
            
            //bottom
            
            this->render_tab_section(x + 15, y + 262, 143, 200);
            draw->drawstring(x + 85, y + 360, nagatoro, osFont, "D", true);
            
            this->render_tab_section(x + 173, y + 262, 143, 200);
            draw->drawstring(x + 243, y + 360, nagatoro, osFont, "C", true);
            
            break;
            
            
        case 1:
            render_section(x + 15, y + 36, 220, h - 60, "Main");
            render_section(x + 254, y + 36, 220, h - 60, "Other");
            this->renderAim(x + 35, y + 30 + 20 + 5);
            break;
            
        case 2:
            render_section(x + 15, y + 36, 220, h - 60, "Main");
            render_section(x + 254, y + 36, 220, h - 60, "Other");
            this->renderAntiAim(x + 35, y + 30 + 20 + 5);
            break;
            
        case 3:
            render_section(x + 15, y + 36, 220, h - 60, "Main");
            render_section(x + 254, y + 36, 220, h - 60, "Other");
            this->renderPlayer(x + 35, y + 30 + 20 + 5);
            break;
            
        case 4:
            render_section(x + 15, y + 36, 220, h - 60, "Main");
            render_section(x + 254, y + 36, 220, h - 60, "Other");
            this->renderMisc(x + 35, y + 30 + 20 + 5);
            break;
            
        case 5:
            render_section(x + 15, y + 36, 220, h - 60, "Main");
            render_section(x + 254, y + 36, 220, h - 60, "Other");
            this->renderColors(x + 35, y + 30 + 20 + 5);
            break;
            
            
            
        default:
            break;
            
    }
    
    config->getConfig(cfg.cfgcombo);
    /*
     if(!vars.cfgInit) {
     skins_cfg->LoadSkins();
     vars.cfgInit = true;
     }*/
    if(cfg.loadconfig) {
        config->LoadConfig();
        skins_cfg->LoadSkins();
    }
    
    if(cfg.saveconfig) {
        config->SaveConfig();
    }
    
    
    
    // Render strings last so they're on top
    /*draw->drawstring(x + 50, y + 22 + 16, white, osFont, "A", true);
     draw->drawstring(x + 150, y + 22 + 17, white, osFont, "J", true);
     draw->drawstring(x + 250, y + 22 + 16, white, osFont, "B", true);
     draw->drawstring(x + 350, y + 22 + 17, white, osFont, "C", true);
     draw->drawstring(x + 450, y + 22 + 15, white, osFont, "G", true);
     */
    
    Pressed(MOUSE_LEFT);
    draw->MoveMenu(x, y, w, hh, 1);
    
}

