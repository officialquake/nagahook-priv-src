//
//  visuals.hpp
//  vHook
//
//  Created by Timothy Dillan on 6/30/19.
//  Copyright © 2019 ViKiNG. All rights reserved.
//

#pragma once

#include "../main.h"

class C_Visuals
{
private:
    
    void draw_esp_box(int x, int y, int w, int h, Color col);
    void draw_skeleton(C_BasePlayer* player);
    
    void draw_planted_bomb(C_BasePlantedC4* bomb);
    void draw_dropped_weapons(C_BaseCombatWeapon* weapon);
    
    void draw_other_esp(C_BaseEntity* entity);
    void draw_player_esp(C_BasePlayer* player);
    
public:
    
    void draw_esp();
    
    void draw_recoil_crosshair();
    
    void render_chams(void* thisptr, void* context, void* state, ModelRenderInfo_t& model_info, matrix3x4_t* pCustomBoneToWorld);
    
};

extern C_Visuals* visuals;
