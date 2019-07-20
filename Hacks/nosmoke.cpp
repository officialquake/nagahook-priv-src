//
//  nosmoke.cpp
//  vHook
//
//  Created by Timothy Dillan on 14/7/19.
//  Copyright © 2019 ViKiNG. All rights reserved.
//

#include "nosmoke.hpp"

C_Smoke* smoke = new C_Smoke();

void C_Smoke::remove_smoke(ClientFrameStage_t stage)
{
    if(!pEngine->IsInGame())
        return;
    
    static bool done;
    static bool last_setting;
    
    const vector<const char*> smoke_materials =
    {
        "particle/beam_smoke_01",
        "particle/particle_smokegrenade",
        "particle/particle_smokegrenade1",
        "particle/particle_smokegrenade2",
        "particle/particle_smokegrenade3",
        "particle/particle_smokegrenade_sc",
        "particle/smoke1/smoke1",
        "particle/smoke1/smoke1_ash",
        "particle/smoke1/smoke1_nearcull",
        "particle/smoke1/smoke1_nearcull2",
        "particle/smoke1/smoke1_snow",
        "particle/smokesprites_0001",
        "particle/smokestack",
        "particle/vistasmokev1/vistasmokev1",
        "particle/vistasmokev1/vistasmokev1_emods",
        "particle/vistasmokev1/vistasmokev1_emods_impactdust",
        "particle/vistasmokev1/vistasmokev1_fire",
        "particle/vistasmokev1/vistasmokev1_nearcull",
        "particle/vistasmokev1/vistasmokev1_nearcull_fog",
        "particle/vistasmokev1/vistasmokev1_nearcull_nodepth",
        "particle/vistasmokev1/vistasmokev1_smokegrenade",
        "particle/vistasmokev1/vistasmokev4_emods_nocull",
        "particle/vistasmokev1/vistasmokev4_nearcull",
        "particle/vistasmokev1/vistasmokev4_nocull"
    };
    
    if(!done)
    {
        for(auto material : smoke_materials)
        {
            IMaterial* mat = pMatSystem->FindMaterial(material, TEXTURE_GROUP_OTHER);
            mat->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, vars.visuals.nosmoke);
        }
        
        done = true;
    }
    
    if(last_setting != vars.visuals.nosmoke)
    {
        last_setting = vars.visuals.nosmoke;
        done = false;
    }
}
