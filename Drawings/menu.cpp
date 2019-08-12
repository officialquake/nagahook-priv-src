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
Color greycolor = Color(189, 195, 199, 255);
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

int RainbowR= 100;
int RainbowG= 100;
int RainbowB= 100;
float RainbowTexts= 100;
//--------------------------------------------------------------------
void DoRainBow(){
    if(RainbowTexts!=100){
        RainbowR-=2,RainbowG-=3,RainbowB-=3;
    }
    
    if(RainbowTexts!=255){
        RainbowR+=2,RainbowG+=3,RainbowB+=4;
    }
}
//--------------------------------------------------------------------
#define RAINBOW            D3DCOLOR_ARGB(255, RainbowR, RainbowG, RainbowB)

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
    
    vector<string> Hitgroup;  // Resolver
    
    Hitgroup.push_back("Head");
    Hitgroup.push_back("Body");
    Hitgroup.push_back("Legs");
    
    /*this->renderCheckbox(x - 15, y, "Enabled", &vars.aimbot.enabled);
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
    this->renderCheckbox(x - 15, y + 200, "Baim Under x HP", &vars.aimbot.baimhp);
    this->renderSlider(x + 5, y + 220, 150, "", vars.aimbot.baimxhp, 100, 0);*/
    
    this->renderCheckbox(x - 15, y + 15, "Legit Aimbot", &vars.aimbot.LegitEnabled);
    this->renderSlider(x + 5, y + 35, 150, "FOV", vars.aimbot.legitFOV, 5.0f, 0.0f);
    this->renderCheckbox(x - 15, y + 55, "Smoothing", &vars.aimbot.smooth);
    this->renderSlider(x + 5, y + 75, 150, "Amount", vars.aimbot.smoothf, 1.0f, 0.0f);
    this->renderCheckbox(x - 15, y + 95, "Target Hitgroup", &vars.aimbot.legitHitscan);
    this->renderCombo(x + 10, y + 115, 150, 20, "Head", Hitgroup, vars.aimbot.legitHitscanType, &vars.legithitscanpri_opend);
    
    this->renderCheckbox(x + 235, y + 15, "Backtrack", &vars.aimbot.backtrack);

    this->renderCheckbox(x + 235, y + 35, "Triggerbot", &vars.aimbot.trigger);
    this->renderCheckbox(x + 235, y + 55, "Radar", &vars.misc.radar);
    
    /**/
    

    
    //this->renderCheckbox(x + 235, y + 280, "Auto Stop", &vars.aimbot.autostop);
    
    
    /*vector<string> hitscan;
    // X
    hitscan.push_back("off");
    hitscan.push_back("low");//xanax moving
    hitscan.push_back("normal");//supremacy $
    hitscan.push_back("high");//gamesense
    hitscan.push_back("extreme");
    hitscan.push_back("baim");
    //CT.push_back("Test 2");
    //CT.push_back("Mixed");
    this->renderCombo(x + 260, y + 120, 150, 20, "Hitscan", hitscan, vars.aimbot.hitscantype, &vars.hitscan_opend);*/
    
    
    
    
    
    
}

void cMenu::renderAntiAim(int x, int y) {
    
    vector<string> fakewalk;  // Fake types
    fakewalk.push_back("Off");
    fakewalk.push_back("v1");
    fakewalk.push_back("v2");
    fakewalk.push_back("v3");
    
    vector<string> Pitch;  // Real Pitch
    vector<string> Yaw;  // Real Yaw
    vector<string> FakeYaw; // Fake Yaw
    vector<string> MY; // Ground Yaw
    vector<string> AY; // Air Yaw
    vector<string> LegitAA; // Air Yaw
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
    Yaw.push_back("LISP");
    Yaw.push_back("SidewaysRight");
    Yaw.push_back("LBYBreaker");
    Yaw.push_back("Desync");
    // Fake Yaw
    // Fake Yaw
    FakeYaw.push_back("Off");
    FakeYaw.push_back("FakeSpin");
    FakeYaw.push_back("FakeLBYHook");
    FakeYaw.push_back("FakeTwoStep");
    FakeYaw.push_back("FakeLowerBody135");
    FakeYaw.push_back("FakeInverseRotation");
    FakeYaw.push_back("Desync");
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
    
    LegitAA.push_back("Off");
    LegitAA.push_back("Backwards");
    LegitAA.push_back("Sideways");
    LegitAA.push_back("Adaptive Side");
    
    this->renderCheckbox(x - 15, y + 15, "Ragebot Enabled", &vars.aimbot.enabled);
    this->renderCheckbox(x - 15, y + 35, "SilentAim", &vars.aimbot.silent);
    //draw->drawstring(x + 5, y + 40, FontColor, mFont, "FOV");
    this->renderSlider(x + 5, y + 55, 150, "FOV", vars.aimbot.FovToPlayer, 180, 0);
    // draw->drawstring(x, y + 70, FontColor, mFont, "Hitbox");
    this->renderSlider(x + 5, y + 75, 150, "Hitbox", vars.aimbot.hitbox, 19, 0);
    this->renderCheckbox(x - 15, y + 95, "Auto Wall", &vars.aimbot.autowall);
    this->renderSlider(x + 5, y + 115, 150, "Minimum Damage", vars.aimbot.mindmg, 100, 0);
    this->renderCheckbox(x - 15, y + 135, "Hitchance", &vars.aimbot.hitchance);
    this->renderSlider(x + 5, y + 155, 150, "", vars.aimbot.accuracyhithcance, 100, 0);
    this->renderSlider(x + 5, y + 180, 150, "Pointscale", vars.aimbot.pointscale, 100, 0);
    this->renderCheckbox(x - 15, y + 200, "Baim Under x HP", &vars.aimbot.baimhp);
    this->renderSlider(x + 5, y + 220, 150, "", vars.aimbot.baimxhp, 100, 0);
    
    this->renderCheckbox(x + 474, y + 15, "Anti-Aim", &vars.misc.antiaim);
    this->renderCheckbox(x + 474, y + 35, "Show Real Angles", &vars.misc.thirdpersonmode);
    this->renderCheckbox(x + 474, y + 55, "AA Turbo Jitter", &vars.misc.turbojizzer);
    this->renderCheckbox(x + 474, y + 75, "AA Back Jitter", &vars.misc.backjizzer);
    this->renderCheckbox(x + 474, y + 95, "AA LBY Spin", &vars.misc.lby_spin);
    this->renderCheckbox(x + 474, y + 115, "AA Edge", &vars.visuals.edge);
    this->renderCheckbox(x + 474, y + 135, "Resolver Fucker", &vars.misc.resolverfucker);
    this->renderCheckbox(x + 474, y + 155, "Anti Resolver Flip", &vars.misc.antiResolverFlip);
    this->renderCheckbox(x + 474, y + 175, "Fake AA", &vars.misc.fakeaa); // 60
    this->renderCombo(x + 474, y + 205, 90, 20, "Pitch", Pitch, vars.misc.aaX, &vars.aaX_opend);
    if(!vars.aaX_opend){
        this->renderCombo(x + 474, y + 235, 90, 20, "Yaw", Yaw, vars.misc.aaY, &vars.aaY_opend);
    }
    if((!vars.aaX_opend) && !vars.aaY_opend) {
        this->renderCombo(x + 474, y + 265, 90, 20, "fYaw", FakeYaw, vars.misc.FaaY, &vars.FaaY_opend);
    }
     this->renderCheckbox(x + 474, y + 295, "LBY Breaker", &vars.misc.lbybreaker); // 60
    this->renderCheckbox(x + 474, y + 315, "LBY Breaker Manual?", &vars.misc.lbybreakermanual); // 60
    this->renderSlider(x + 474, y + 345, 130, "LBY Breaker Offset", vars.misc.lbybreakeroffset, 360.f, 0.f);
    this->renderCheckbox(x + 474, y + 375, "Legit AA", &vars.misc.legitaa); // 60
    this->renderCombo(x + 474, y + 395, 150, 20, "Off", LegitAA, vars.aimbot.legitaatype, &vars.legitaa_opend);
    
    //this->renderCheckbox(x - 15, y + 160, "Freestand", &vars.aimbot.freestand);
    this->renderCheckbox(x + 235, y + 15, "Fakewalk", &vars.aimbot.fakewalk);
    this->renderCombo(x + 235, y + 32, 90, 20, "Fakewalk", fakewalk, vars.aimbot.fakewalktype, &vars.fakewalk_opend);
    this->renderCheckbox(x + 235, y + 55, "Auto Scope", &vars.aimbot.autoscope);
    this->renderCheckbox(x + 235, y + 75, "Auto Pistol", &vars.aimbot.autopistol);
    this->renderCheckbox(x + 235, y + 95, "Auto Crouch", &vars.aimbot.autocrouch);
    this->renderCheckbox(x + 235, y + 115, "Auto Shoot", &vars.aimbot.autoshoot);
    this->renderCheckbox(x + 235, y + 135, "Hitscan", &vars.aimbot.hitscan);
    vector<string> hitscan;
    // X
    hitscan.push_back("off");
    hitscan.push_back("low");//xanax moving
    hitscan.push_back("normal");//supremacy $
    hitscan.push_back("high");//gamesense
    hitscan.push_back("extreme");
    hitscan.push_back("baim");
    //CT.push_back("Test 2");
    //CT.push_back("Mixed");
    this->renderCombo(x + 235, y + 155, 150, 20, "Off", hitscan, vars.aimbot.hitscantype, &vars.hitscan_opend);
    this->renderCheckbox(x + 235, y + 185, "Moonwalk", &vars.misc.moonwalk);
    
    /*if (!vars.freestand_opend) {
        this->renderSlider(x - 5, y + 180, 150, "Jitter", vars.aimbot.jitter, 180, 0);
    }*/
    vector<string> Resolve;  // Resolver
    
    
    Resolve.push_back("Experimental");
    Resolve.push_back("LBYResolver");
    Resolve.push_back("Smart");
    Resolve.push_back("Evolution");
    Resolve.push_back("Test");
    Resolve.push_back("Synp1");
    Resolve.push_back("Best Resolver");
    
    
    
    this->renderCheckbox(x + 235, y + 205, "Yaw Resolver", &vars.aimbot.Yawresolver);
    
    this->renderCombo(x + 235, y + 225, 90, 20, "Off", Resolve, vars.aimbot.yresolve, &vars.resolver_opend); // 150
    
    
}

void cMenu::renderVis(int x, int y) {
    
    vector<string> Players;
    vector<string> Hands;
    vector<string> Weapons;
    vector<string> fakelag;
    vector<string> localchams;
    
    Players.push_back("Platinum");
    Players.push_back("Texture");
    Players.push_back("WireFrame");
    Players.push_back("Crystal Blue");
    Players.push_back("Mexican Cartel");
    Players.push_back("Fading");
    Players.push_back("Glass");
    Players.push_back("Gold");
    Players.push_back("Red Glow");
    Players.push_back("Fishing Net");
    Players.push_back("Branches");
    Players.push_back("Plastic");
    
    Hands.push_back("Platinum");
    Hands.push_back("Texture");
    Hands.push_back("Wireframe");
    Hands.push_back("Crystal Blue");
    Hands.push_back("Mexican Cartel");
    Hands.push_back("Fading");
    Hands.push_back("Glass");
    Hands.push_back("Gold");
    Hands.push_back("Red Glow");
    Hands.push_back("Fishing Net");
    Hands.push_back("Branches");
    Hands.push_back("Plastic");
    
    Weapons.push_back("Platinum");
    Weapons.push_back("Texture");
    Weapons.push_back("Wireframe");
    Weapons.push_back("Crystal Blue");
    Weapons.push_back("Mexican Cartel");
    Weapons.push_back("Fading");
    Weapons.push_back("Glass");
    Weapons.push_back("Gold");
    Weapons.push_back("Red Glow");
    Weapons.push_back("Fishing Net");
    Weapons.push_back("Branches");
    Weapons.push_back("Plastic");
    
    fakelag.push_back("Platinum");
    fakelag.push_back("Texture");
    fakelag.push_back("Wireframe");
    fakelag.push_back("Crystal Blue");
    fakelag.push_back("Mexican Cartel");
    fakelag.push_back("Fading");
    fakelag.push_back("Glass");
    fakelag.push_back("Gold");
    fakelag.push_back("Red Glow");
    fakelag.push_back("Fishing Net");
    fakelag.push_back("Branches");
    fakelag.push_back("Plastic");
    
    localchams.push_back("Platinum");
    localchams.push_back("Texture");
    localchams.push_back("Wireframe");
    localchams.push_back("Crystal Blue");
    localchams.push_back("Mexican Cartel");
    localchams.push_back("Fading");
    localchams.push_back("Glass");
    localchams.push_back("Gold");
    localchams.push_back("Red Glow");
    localchams.push_back("Fishing Net");
    localchams.push_back("Branches");
    localchams.push_back("Plastic");
    localchams.push_back("Lit");
    
    this->renderCheckbox(x - 15, y + 15, "Enabled", &vars.visuals.enabled);
    this->renderCheckbox(x - 15, y + 35, "Enemy only", &vars.visuals.enemyonly);
    this->renderCheckbox(x - 15, y + 55, "Vis Only", &vars.visuals.visonly);
    this->renderCheckbox(x - 15, y + 75, "Box", &vars.visuals.box);
    this->renderCheckbox(x - 15, y + 95, "Name", &vars.visuals.name);
    this->renderCheckbox(x - 15, y + 115, "Health", &vars.visuals.health);
    this->renderCheckbox(x - 15, y + 135, "Armour", &vars.visuals.armour);
    this->renderCheckbox(x - 15, y + 155, "Heath text", &vars.visuals.healthtext);
    this->renderCheckbox(x - 15, y + 175, "Skeleton", &vars.visuals.skeleton);
    this->renderCheckbox(x - 15, y + 195, "Snaplines", &vars.visuals.snapline);
    this->renderCheckbox(x - 15, y + 215, "Grenade ESP", &vars.visuals.grenade);
    this->renderCheckbox(x - 15, y + 235, "Weapon ESP", &vars.visuals.active);
    

    this->renderCheckbox(x - 15, y + 255, "Player Chams", &vars.visuals.chams);
    this->renderCheckbox(x - 15, y + 275, "Hand Chams", &vars.visuals.handchams);
    this->renderCheckbox(x - 15, y + 295, "Weapon Chams", &vars.visuals.weaponchams);
    this->renderCheckbox(x - 15, y + 315, "Fake Lag Chams", &vars.misc.flagchams);
    this->renderCheckbox(x - 15, y + 335, "Local Player Chams", &vars.visuals.localchams);
    
    if(vars.visuals.chams) {
        this->renderCombo(x + 10, y + 355, 150, 20, "Platinum", Players, vars.visuals.playersType, &vars.players_opend);
    }
    if(vars.visuals.handchams) {
        if(!vars.players_opend)
            this->renderCombo(x + 10, y + 375, 150, 20, "Platinum", Hands, vars.visuals.handsType, &vars.hands_opend);
    }
    if(vars.visuals.weaponchams) {
        if((!vars.players_opend) && !vars.hands_opend)
            this->renderCombo(x + 10, y + 395, 150, 20, "Platinum", Weapons, vars.visuals.weaponType, &vars.weapons_opend);
    }
    if(vars.misc.flagchams) {
        if(!vars.players_opend)
            this->renderCombo(x + 10, y + 415, 150, 20, "Platinum", fakelag, vars.visuals.fakelagtype, &vars.fakelag_opend);
    }
    if(vars.visuals.localchams) {
        if(!vars.players_opend)
            this->renderCombo(x + 10, y + 435, 150, 20, "Platinum", localchams, vars.visuals.localchamstype, &vars.local_opend);
    }
    
    
    int iScreenWidth, iScreenHeight;
    pEngine->GetScreenSize(iScreenWidth, iScreenHeight);
    
    //Middle
    this->renderCheckbox(x + 235, y + 15, "SkinChanger", & vars.visuals.skinc);
    this->renderCheckbox(x + 235, y + 35, "Dropped Weapons", & vars.visuals.weapons);
    this->renderCheckbox(x + 235, y + 55, "Bomb Timer", & vars.visuals.bombtimer);
    this->renderCheckbox(x + 235, y + 75, "Defusing", & vars.visuals.defusing);
    this->renderCheckbox(x + 235, y + 95, "Rescuing", & vars.visuals.rescuing);
    this->renderCheckbox(x + 235, y + 115, "Scoping", & vars.visuals.scoped);
    this->renderCheckbox(x + 235, y + 135, "No Flash", & vars.misc.noflash);
    this->renderSlider(x + 230, y + 155, 150, "", vars.misc.flashalpha, 255, 0);
    this->renderCheckbox(x + 235, y + 175, "Recoil Crosshair", & vars.visuals.rcrosshair);
    this->renderCheckbox(x + 235, y + 195, "Spread Crosshair", &vars.misc.spreadcrosshair);
    this->renderCheckbox(x + 235, y + 215, "No Scope", & vars.misc.noscope);
    this->renderCheckbox(x + 235, y + 235, "AA Indicators", & vars.visuals.antiaim_indicator);
    std::vector<std::string> Indicator;
    
    Indicator.push_back("Off");
    Indicator.push_back("Words");
    Indicator.push_back("Arrows");
    
    this->renderCombo(x + 235, y + 252, 125, 20, "Off", Indicator, vars.visuals.indicatorAA_types, &vars.indicatorAA_opend);
    this->renderCheckbox(x + 235, y + 275, "AA Lines", & vars.visuals.aaline);
    this->renderCheckbox(x + 235, y + 295, "Angle Line Names", & vars.visuals.anglelinenames);
    this->renderCheckbox(x + 235, y + 315, "Watermark", &vars.misc.watermark);
    this->renderCheckbox(x + 235, y + 335, "Nightmode", &vars.misc.nightmode);
    this->renderSlider(x + 230, y + 355, 150, "Player Chams", vars.visuals.playerchams_alpha, 255, 0);
    this->renderSlider(x + 230, y + 375, 150, "Hand Chams", vars.visuals.handchams_alpha, 255, 0);
    this->renderSlider(x + 230, y + 395, 150, "Weapon Chams", vars.visuals.weaponchams_alpha, 255, 0);
    this->renderSlider(x + 230, y + 415, 150, "Fake Lag Chams", vars.visuals.fakelagchams_alpha, 255, 0);
    this->renderSlider(x + 230, y + 435, 150, "Local Player Chams", vars.visuals.localchams_alpha, 255, 0);
    this->renderCheckbox(x + 235, y + 455, "Asuswall", &vars.misc.asuswalls);
    this->renderSlider(x + 230, y + 475, 150, "", vars.misc.asusalpha, 1.f, 0.f);
    
    this->renderCheckbox(x + 474, y + 15, "Hitmarker", &vars.visuals.hitmarker);
    this->renderCheckbox(x + 474, y + 35, "Hitmarker Sounds", &vars.visuals.hitmarkersounds);
    this->renderSlider(x + 474, y + 55, 150, "Hitmarker Size", vars.visuals.hitsize, 32, 0);
    this->renderSlider(x + 474, y + 75, 150, "Hitmarker Duration", vars.visuals.hitduration, 3000, 0);
    this->renderSlider(x + 474, y + 95, 150, "Hitmarker In-Gap", vars.visuals.hitinnergap, 16, 0);
    this->renderCheckbox(x + 474, y + 115, "Hitmarker Allies", &vars.visuals.allieshit);
    this->renderCheckbox(x + 474, y + 135, "Hitmarker Enemies", &vars.visuals.enemyhit);
    this->renderCheckbox(x + 474, y + 155, "Left-Hand Knife", &vars.visuals.inverseragdoll);
    this->renderCheckbox(x + 474, y + 175, "Sniper Crosshair", &vars.misc.snipercrosshair);
    this->renderCheckbox(x + 474, y + 195, "Show Enemies Log", &vars.misc.showenemieslog);
    this->renderCheckbox(x + 474, y + 215, "Show Allies Log", &vars.misc.showallieslog);
    this->renderSlider(x + 474, y + 245, 130, "Logger Duration", vars.misc.loggerduration, 3000.f, 0.f);
    this->renderSlider(x + 474, y + 275, 130, "Logger Lines", vars.misc.loggerlines, 15, 0);
    this->renderCheckbox(x + 474, y + 315, "Show local player", &vars.misc.showlocalplayer);
}


void cMenu::renderMisc(int x, int y) {
    
    vector<string> CT;
    // X
    CT.push_back("off");
    CT.push_back("xanax");//xanax moving
    CT.push_back("supremacy");//supremacy $
    CT.push_back("gamesense");//gamesense
    CT.push_back("zeus");
    
    vector<string> fakeping;
    // X
    fakeping.push_back("v1");
    fakeping.push_back("v2");//xanax moving

    
    this->renderCheckbox(x - 15, y + 15, "Bhop", &vars.misc.bhop);
    this->renderCheckbox(x - 15, y + 35, "Auto strafe", &vars.misc.autostrafe);
    this->renderCheckbox(x - 15, y + 55, "Circle Strafe", &vars.misc.cstrafe);
    this->renderCheckbox(x - 15, y + 75, "FOV Changer", &vars.misc.fovt);
    this->renderSlider(x - 5, y + 95, 150, "", vars.misc.fov, 70, 0);
    this->renderCheckbox(x - 15, y + 115, "No recoil", &vars.misc.norecoil);
    this->renderCheckbox(x - 15, y + 135, "No visual recoil", &vars.misc.novisual);
    this->renderCheckbox(x - 15, y + 155, "Chat Spam", &vars.misc.spammer);
    this->renderCheckbox(x - 15, y + 175, "Thirdperson", &vars.misc.thirdperson);
    this->renderSlider(x - 5, y + 195, 150, "", vars.misc.tpoffset, 200, 0);
    
    this->renderCheckbox(x + 235, y + 15, "WorldPaint", &vars.misc.worldpaint);
    this->renderCheckbox(x + 235, y + 35, "Spec List", &vars.misc.showspectators);
    this->renderCheckbox(x + 235, y + 55, "Antiscreenshot", &vars.misc.antiscreenshot);
    this->renderCheckbox(x + 235, y + 75, "Anti untrust", &vars.misc.antiuntrust);
    
    this->renderCheckbox(x + 235, y + 95, "Clantag", & vars.misc.clantag);
    this->renderCheckbox(x + 235, y + 115, "No Smoke", &vars.visuals.nosmoke);
    this->renderCheckbox(x + 235, y + 135, "No Duck Cooldown", &vars.misc.noduckcooldown);
    this->renderCheckbox(x + 235, y + 155, "Anti afk-kick", &vars.visuals.antiafkkick);
    
    this->renderCheckbox(x + 474, y + 15, "Fake Lag", &vars.misc.fakelag);
    this->renderCheckbox(x + 474, y + 35, "Adaptive", &vars.misc.adaptive);
    //this->renderCheckbox(x + 235, y + 220, "Fake Lag Chams", &vars.misc.flagchams);
    this->renderSlider(x + 469, y + 55, 150, "Fake Lag Factor", vars.misc.fakelagfactor, 16, 0);
    this->renderCheckbox(x + 474, y + 75, "FakePing", &vars.misc.fakeping);
    this->renderCombo(x + 474, y + 95,  150, 20, "v1", fakeping, vars.misc.fakepingtype, &vars.fakeping_opend);
    this->renderSlider(x + 469, y + 124, 150, "Fake Ping Value", vars.misc.fakepingvalue, 5, 0);
    

   
    
}

void cMenu::renderColors(int x, int y) {
    
    vector<string> Colors;
    
    Colors.push_back("CT Colours");
    Colors.push_back("T Colours");
    Colors.push_back("Hand/Weapon Colours");
    Colors.push_back("World Colours");
    Colors.push_back("FakeLag Colours");
    Colors.push_back("TP Colours");
    Colors.push_back("Local Colours");

    this->renderCombo(x, y + 300 + 14, 125, 20, "CT Colours", Colors, vars.colors.combo, &vars.colors_opend);
    
    if(vars.colors.combo == 0) {
        this->drawcolorpicker(x, y + 30, "CT Box", vars.colors.ctbox);
        this->drawcolorpicker(x, y + 170, "CT BoxIgn", vars.colors.ctbox_ign);
        this->drawcolorpicker(x + 235, y + 30, "CT Chams", vars.colors.ctchams);
        this->drawcolorpicker(x + 235, y + 170, "CT ChamIgn", vars.colors.ctchams_ign);
    }
    if(vars.colors.combo == 1) {
        this->drawcolorpicker(x, y + 30, "T Box", vars.colors.tbox);
        this->drawcolorpicker(x, y + 170, "T BoxIgn", vars.colors.tbox_ign);
        this->drawcolorpicker(x + 235, y + 30, "T Chams", vars.colors.tchams);
        this->drawcolorpicker(x + 235, y + 170, "T ChamIgn", vars.colors.tchams_ign);
    }
    if(vars.colors.combo == 2) {
        this->drawcolorpicker(x, y + 30, "Hands", vars.colors.hands);
        this->drawcolorpicker(x + 235, y + 30, "Weapon", vars.colors.weapon);
    }
    if(vars.colors.combo == 3) {
        this->drawcolorpicker(x, y + 30, "World", vars.colors.world);
        this->drawcolorpicker(x + 235, y + 30, "Sky", vars.colors.sky);
    }
    if(vars.colors.combo == 4) {
        this->drawcolorpicker(x, y + 30, "FakeLag", vars.colors.fakelag);

    }
    if(vars.colors.combo == 5) {
        this->drawcolorpicker(x, y + 30, "TP", vars.colors.scopedchams);
        
    }
    if(vars.colors.combo == 6) {
        this->drawcolorpicker(x, y + 30, "Colors", vars.colors.localchams);
        
    }

}

void cMenu::renderConfigs(int x, int y) {
    vector<string> conf;
    
    conf.push_back("scout");
    conf.push_back("autos");
    conf.push_back("legit");
    conf.push_back("rage");
    conf.push_back("rifles");
    
    this->renderCombo(x, y + 265,  150, 20, "scout", conf, cfg.cfgcombo, &vars.cfg_opend);
    if(!vars.cfg_opend) {
        this->renderButton(x, y + 285, "Save", &cfg.saveconfig);
        this->renderButton(x + 85, y + 285, "Load", &cfg.loadconfig);
        
    }
}

void cMenu::renderCredits(int x, int y) {
    draw->drawstring(x + 15, y + 25, nagatoro, osFont, "ViKiNG", true);
    draw->drawstring(x + 15, y + 45, nagatoro, osFont, "-X/Syn", true);
    draw->drawstring(x + 15, y + 65, nagatoro, osFont, "Pwned", true);
    draw->drawstring(x + 15, y + 85, nagatoro, osFont, "Warlauke", true);
    draw->drawstring(x + 15, y + 105, nagatoro, osFont, "CreditCode", true);
    draw->drawstring(x + 15, y + 125, nagatoro, osFont, "Gael", true);
    draw->drawstring(x + 15, y + 145, nagatoro, osFont, "Tim", true);
    
    draw->drawstring(x + 250, y + 25, nagatoro, osFont, "Nagatoro", true);

}

// Menu tabs
enum mTab
{
    Main    = 0,
    LegitBot  = 1,
    RageBot   = 2,
    Visuals  = 3,
    Misc = 4,
    ColorsTab = 5,
    ConfigTab = 6,
    Credits = 7
    
};

static int curTab = mTab::Credits;

// This is where the menu is "put together"
void cMenu::renderMenu() {
    
    static int x = 100;
    static int y = 100;
    int w = 710;
    int h = 600;
    int hh = 22; // The height of the dragable area
    
    
    
    draw->fillrgba(x, y, w, h, Color(28, 28, 28, 255));
    draw->fillrgba(x, y + 19, w, 3, Color(255, 0, 0, 255));
    static int counter = 0;
    static float colors[3] = { 1.f, 0.f, 0.f };
    
    if (colors[counter] >= 1.0f)
    {
        colors[counter] = 1.0f;
        counter += 1;
        if (counter > 2)
            counter = 0;
    }
    else
    {
        int prev = counter - 1;
        if (prev < 0) prev = 2;
        colors[prev] -= 0.05f;
        colors[counter] += 0.05f;
    }
    draw->drawstring(x + ( ( w - 4 ) / 2 ) + 2, y + 10, Color(colors[0] * 255, colors[1] * 255, colors[2] * 255, 255), csgo_icons, "q", true);
    
    // Draws tabs
    draw->RectOutlined(x + 7, y + 18 + 7, 96, 25, 1, Color(18, 18, 18, 255), Color(colors[0] * 255, colors[1] * 255, colors[2] * 255, 255));
    draw->RectOutlined(x + 107, y + 18 + 7, 96, 25, 1, Color(18, 18, 18, 255), Color(colors[0] * 255, colors[1] * 255, colors[2] * 255, 255));
    draw->RectOutlined(x + 207, y + 18 + 7, 96, 25, 1, Color(18, 18, 18, 255), Color(colors[0] * 255, colors[1] * 255, colors[2] * 255, 255));
    draw->RectOutlined(x + 307, y + 18 + 7, 96, 25, 1, Color(18, 18, 18, 255), Color(colors[0] * 255, colors[1] * 255, colors[2] * 255, 255));
    draw->RectOutlined(x + 407, y + 18 + 7, 96, 25, 1, Color(18, 18, 18, 255), Color(colors[0] * 255, colors[1] * 255, colors[2] * 255, 255));
    draw->RectOutlined(x + 507, y + 18 + 7, 96, 25, 1, Color(18, 18, 18, 255), Color(colors[0] * 255, colors[1] * 255, colors[2] * 255, 255));
    draw->RectOutlined(x + 607, y + 18 + 7, 96, 25, 1, Color(18, 18, 18, 255), Color(colors[0] * 255, colors[1] * 255, colors[2] * 255, 255));
    
    
    // Handles tabs
    if(draw->inArea(x + 2, y + 27, 96, 20)) {
        
        draw->RectOutlined(x + 2, y + 20 + 5, 96, 25, 1, Color(12, 12, 12, 255), greycolor);
        
        if(WasReleased)
            curTab = mTab::LegitBot;
        
    } else if(draw->inArea(x + 102, y + 27, 96, 20)) {
        
        draw->RectOutlined(x + 102, y + 20 + 5, 96, 25, 1, Color(12, 12, 12, 255), greycolor);
        
        if(WasReleased)
            curTab = mTab::RageBot;
        
    } else if(draw->inArea(x + 202, y + 27, 96, 20)) {
        
        draw->RectOutlined(x + 202, y + 20 + 5, 96, 25, 1, Color(12, 12, 12, 255), greycolor);
        
        if(WasReleased)
            curTab = mTab::Visuals;
        
    } else if(draw->inArea(x + 302, y + 27, 96, 20)) {
        
        draw->RectOutlined(x + 302, y + 20 + 5, 96, 25, 1, Color(12, 12, 12, 255), greycolor);
        
        if(WasReleased)
            curTab = mTab::Misc;
        
    } else if(draw->inArea(x + 402, y + 27, 96, 20)) {
        
        draw->RectOutlined(x + 402, y + 20 + 5, 96, 25, 1, Color(12, 12, 12, 255), greycolor);
        
        if(WasReleased)
            curTab = mTab::ColorsTab;
        
    } else if(draw->inArea(x + 502, y + 27, 96, 20)) {
        
        draw->RectOutlined(x + 502, y + 20 + 5, 96, 25, 1, Color(12, 12, 12, 255), greycolor);
        
        if(WasReleased)
            curTab = mTab::ConfigTab;
            
    } else if(draw->inArea(x + 602, y + 27, 96, 20)) {
        
        draw->RectOutlined(x + 602, y + 20 + 5, 96, 25, 1, Color(12, 12, 12, 255), greycolor);
        
        if(WasReleased)
            curTab = mTab::Credits;
    }
    
    
    
    switch (curTab) {
            
        case mTab::LegitBot:
            render_section(x + 10, y + 55, 220, h - 62, "Main");
            render_section(x + 249, y + 55, 220, h - 62, "Other");
            this->renderAim(x + 35, y + 30 + 20 + 5);
            break;
            
        case mTab::RageBot:
            render_section(x + 10, y + 55, 220, h - 62, "Main");
            render_section(x + 249, y + 55, 220, h - 62, "Other");
            render_section(x + 488, y + 55, 220, h - 62, "Anti-Aim");
            this->renderAntiAim(x + 35, y + 30 + 20 + 5);
            break;
            
        case mTab::Visuals:
            render_section(x + 10, y + 55, 220, h - 62, "Main");
            render_section(x + 249, y + 55, 220, h - 62, "Other");
            render_section(x + 488, y + 55, 220, h - 62, "Other2");
            this->renderVis(x + 35, y + 30 + 20 + 5);
            break;
            
        case mTab::Misc:
            render_section(x + 10, y + 55, 220, h - 62, "Main");
            render_section(x + 249, y + 55, 220, h - 62, "Other");
            render_section(x + 488, y + 55, 220, h - 62, "HvH");
            this->renderMisc(x + 35, y + 30 + 20 + 5);
            break;
            
        case mTab::ColorsTab:
            render_section(x + 10, y + 55, 220, h - 62, "Main");
            render_section(x + 249, y + 55, 220, h - 62, "Other");
            this->renderColors(x + 35, y + 30 + 20 + 5);

            break;
            
        case mTab::ConfigTab:
            render_section(x + 10, y + 55, 220, h - 62, "Main");
            this->renderConfigs(x + 35, y + 30 + 20 + 5);
            break;
            
        case mTab::Credits:
            render_section(x + 10, y + 55, 220, h - 62, "Main Contributors");
            render_section(x + 249, y + 55, 220, h - 62, "Others");
            this->renderCredits(x + 35, y + 30 + 20 + 5);
            break;
            
        default:
            break;
            
    }

    config->getConfig(cfg.cfgcombo);

    if(cfg.loadconfig) {
        config->LoadConfig();
        skins_cfg->LoadSkins();
    }
    
    if(cfg.saveconfig) {
        config->SaveConfig();
    }
    
    draw->drawstring(x + 50, y + 22 + 16, Color::White(), osFont, "LEGITBOT", true);
    draw->drawstring(x + 150, y + 22 + 17, Color::White(), osFont, "RAGEBOT", true);
    draw->drawstring(x + 250, y + 22 + 16, Color::White(), osFont, "VISUALS", true);
    draw->drawstring(x + 350, y + 22 + 16, Color::White(), osFont, "MISC", true);
    draw->drawstring(x + 450, y + 22 + 15, Color::White(), osFont, "COLORS", true);
    draw->drawstring(x + 550, y + 22 + 15, Color::White(), osFont, "CONFIG", true);
    draw->drawstring(x + 650, y + 22 + 15, Color::White(), osFont, "CREDITS", true);
    
    Pressed(MOUSE_LEFT);
    draw->MoveMenu(x, y, w, hh, 1);
}

