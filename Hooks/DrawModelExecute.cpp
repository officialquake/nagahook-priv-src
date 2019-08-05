#include "main.h"
#include "DrawModelExecute.h"
string DirName(string source)
{
    source.erase(find(source.rbegin(), source.rend(), '/').base(), source.end());
    return source;
}

string GetWorkingPath()
{
    char pathbuf[PROC_PIDPATHINFO_MAXSIZE];
    proc_pidpath(getpid(), pathbuf, sizeof(pathbuf));
    auto dirname = DirName(pathbuf);
    return dirname;
}

bool IsFileExists(const string& name)
{
    int res = access(name.c_str(), R_OK);
    if (res < 0)
    {
        if (errno == ENOENT)
        {
            return false;
        }
        else if (errno == EACCES)
        {
            return true;
        }
        else
        {
            return true;
        }
    }
    return true;
}

void AddMaterial(string filename, string type, bool ignorez, bool wireframe)
{
    if (!IsFileExists(GetWorkingPath().append("csgo/materials/").append(filename).append(".vmt")))
    {
        stringstream ss;
        
        ss << "\"" + type + "\"\n" << endl;
        ss << "{\n" << endl;
        ss << "\t\"$basetexture\" \"VGUI/white_additive\"\n" << endl;
        ss << "\t\"$nofog\" \"1\"\n" << endl;
        ss << "\t\"$ignorez\" \"" + to_string(ignorez) + "\"\n" << endl;
        ss << "\t\"$wireframe\" \""+ to_string(wireframe) +"\"\n" << endl;
        ss << "\t\"$halflambert\" \"1\"\n" << endl;
        
        ss << "}\n" << endl;
        
        ofstream(GetWorkingPath().append("csgo/materials/").append(filename).append(".vmt").c_str()) << ss.str();
    }
}

IMaterial* CreateMaterial(bool ignorez, bool wireframe, string szType)
{
    IMaterial* createdMaterial = nullptr;
    
    
    if(szType == "VertexLitGeneric")
    {
        if(ignorez)
        {
            if (!IsFileExists(GetWorkingPath().append("csgo/materials/").append("barbossa_chamsmat_textured_ignorez").append(".vmt")))
            {
                AddMaterial("barbossa_chamsmat_textured_ignorez", szType, ignorez, wireframe);
            }
            createdMaterial = pMatSystem->FindMaterial("barbossa_chamsmat_textured_ignorez", TEXTURE_GROUP_MODEL);
        }
        else
        {
            if (!IsFileExists(GetWorkingPath().append("csgo/materials/").append("barbossa_chamsmat_textured").append(".vmt")))
            {
                AddMaterial("barbossa_chamsmat_textured", szType, ignorez, wireframe);
            }
            createdMaterial = pMatSystem->FindMaterial("barbossa_chamsmat_textured", TEXTURE_GROUP_MODEL);
        }
    }
    
    
    if(szType == "UnlitGeneric")
    {
        if(ignorez)
        {
            if (!IsFileExists(GetWorkingPath().append("csgo/materials/").append("barbossa_chamsmat_unlit_ignorez").append(".vmt")))
            {
                AddMaterial("barbossa_chamsmat_unlit_ignorez", szType, ignorez, wireframe);
            }
            
            createdMaterial = pMatSystem->FindMaterial("barbossa_chamsmat_unlit_ignorez", TEXTURE_GROUP_MODEL);
        }
        else
        {
            if (!IsFileExists(GetWorkingPath().append("csgo/materials/").append("barbossa_chamsmat_unlit").append(".vmt")))
            {
                AddMaterial("barbossa_chamsmat_unlit", szType, ignorez, wireframe);
            }
            
            createdMaterial = pMatSystem->FindMaterial("barbossa_chamsmat_unlit", TEXTURE_GROUP_MODEL);
        }
    }
    
    
    if(szType == "WireFrame")
    {
        if(ignorez)
        {
            if (!IsFileExists(GetWorkingPath().append("csgo/materials/").append("barbossa_chamsmat_unlit_ignorez_wirefame").append(".vmt")))
            {
                AddMaterial("barbossa_chamsmat_unlit_ignorez_wireframe", szType, ignorez, true);
            }
            
            createdMaterial = pMatSystem->FindMaterial("barbossa_chamsmat_unlit_ignorez_wireframe", TEXTURE_GROUP_MODEL);
        }
        else
        {
            if (!IsFileExists(GetWorkingPath().append("csgo/materials/").append("barbossa_chamsmat_unlit_wireframe").append(".vmt")))
            {
                AddMaterial("barbossa_chamsmat_unlit_wireframe", szType, ignorez, true);
            }
            
            createdMaterial = pMatSystem->FindMaterial("barbossa_chamsmat_unlit_wireframe", TEXTURE_GROUP_MODEL);
        }
    }
    
    createdMaterial->IncrementReferenceCount();
    return createdMaterial;
}



void CallOriginalModel(void* thisptr, void* context, void *state, const ModelRenderInfo_t &pInfo, matrix3x4_t* pCustomBoneToWorld)
{
    modelVMT->GetOriginalMethod<tDrawModelExecute>(21)(thisptr, context, state, pInfo, pCustomBoneToWorld);
}

void hkDrawModelExecute(void* thisptr, void* context, void *state, const ModelRenderInfo_t &pInfo, matrix3x4_t* pCustomBoneToWorld)
{
    
    static IMaterial* firstLayer = CreateMaterial(false, false, "VertexLitGeneric");
    static IMaterial* secondLayer = CreateMaterial(true, false, "VertexLitGeneric");
    
    static IMaterial* firstLit = CreateMaterial(false, false, "UnlitGeneric");
    static IMaterial* secondLit = CreateMaterial(true, false, "UnlitGeneric");
    
    static IMaterial* firstWire = CreateMaterial(false, true, "WireFrame");
    static IMaterial* secondWire = CreateMaterial(true, true, "WireFrame");
    
    static IMaterial* Plastic = pMatSystem->FindMaterial("models/inventory_items/trophy_majors/crystal_blue", TEXTURE_GROUP_OTHER);
    static IMaterial* Glass = pMatSystem->FindMaterial("models/inventory_items/cologne_prediction/cologne_prediction_glass", TEXTURE_GROUP_OTHER);
    static IMaterial* Gold = pMatSystem->FindMaterial("models/inventory_items/trophy_majors/crystal_clear", TEXTURE_GROUP_OTHER);
    static IMaterial* crystal = pMatSystem->FindMaterial("models/inventory_items/dogtags/dogtags_outline", TEXTURE_GROUP_OTHER);
    static IMaterial* Mp3 = pMatSystem->FindMaterial("models/inventory_items/wildfire_gold/wildfire_gold_detail", TEXTURE_GROUP_OTHER);
    static IMaterial* Random = pMatSystem->FindMaterial("dev/glow_armsrace.vmt", TEXTURE_GROUP_OTHER);
    static IMaterial* Random1 = pMatSystem->FindMaterial("models/props_shacks/fishing_net01", TEXTURE_GROUP_OTHER);
    static IMaterial* Random2 = pMatSystem->FindMaterial("models/props_foliage/urban_tree03_branches", TEXTURE_GROUP_OTHER);
    static IMaterial* Random3 = pMatSystem->FindMaterial("models/inventory_items/trophy_majors/gloss", TEXTURE_GROUP_OTHER);
    static IMaterial* Random4 = pMatSystem->FindMaterial("models/player/ct_fbi/ct_fbi_glass", TEXTURE_GROUP_OTHER);
    
    if(pInfo.pModel)
    {
        string pszModel = pModelInfo->GetModelName(pInfo.pModel);
        
        if(vars.misc.antiscreenshot && pEngine->IsTakingScreenshot())
        {
            CallOriginalModel(thisptr, context, state, pInfo, pCustomBoneToWorld);
            pModelRender->ForcedMaterialOverride(NULL);
            return;
        }
        
        
        for (MaterialHandle_t i = pMatSystem->FirstMaterial(); i != pMatSystem->InvalidMaterial(); i = pMatSystem->NextMaterial(i))
        {
            IMaterial *pMaterial = pMatSystem->GetMaterial(i);
            
            if (!pMaterial)
                continue;
            
            if(!vars.misc.worldpaint)
                continue;
            
            if (strstr(pMaterial->GetTextureGroupName(), TEXTURE_GROUP_WORLD))
            {
                pMaterial->ColorModulate(vars.colors.world);
            }
            
        }
        
        // Weapon Chams
        if(pszModel.find("weapons") != string::npos  && vars.visuals.weaponchams)
        {
            IMaterial* materialCheckFirst = [&]() -> IMaterial*
            {
                if(vars.visuals.weaponType == 0)
                    return Random4;
                else if(vars.visuals.weaponType == 1)
                    return firstLayer;
                else if (vars.visuals.weaponType == 2)
                    return firstWire;
                else if(vars.visuals.weaponType == 3)
                    return Plastic;
                else if(vars.visuals.weaponType == 4)
                    return Gold;
                else if(vars.visuals.weaponType == 5)
                    return crystal;
                else if(vars.visuals.weaponType == 6)
                    return Glass;
                else if(vars.visuals.weaponType == 7)
                    return Mp3;
                else if(vars.visuals.weaponType == 8)
                    return Random;
                else if(vars.visuals.weaponType == 9)
                    return Random1;
                else if(vars.visuals.weaponType == 10)
                    return Random2;
                else if(vars.visuals.weaponType == 11)
                    return Random3;
            }();
            
            materialCheckFirst->ColorModulate(vars.colors.weapon);
            materialCheckFirst->AlphaModulate(vars.visuals.weaponchams_alpha / 255.f);
            pModelRender->ForcedMaterialOverride(materialCheckFirst);
            CallOriginalModel(thisptr, context, state, pInfo, pCustomBoneToWorld);
        }
        
        
        // Hand Chams
        if(pszModel.find("arms") != string::npos && vars.visuals.handchams)
        {
            IMaterial* materialCheckFirst = [&]() -> IMaterial*
            {
                if(vars.visuals.handsType == 0)
                    return Random4;
                else if(vars.visuals.handsType == 1)
                    return firstLayer;
                else if (vars.visuals.handsType == 2)
                    return firstWire;
                else if(vars.visuals.handsType == 3)
                    return Plastic;
                else if(vars.visuals.handsType == 4)
                    return Gold;
                else if(vars.visuals.handsType == 5)
                    return crystal;
                else if(vars.visuals.handsType == 6)
                    return Glass;
                else if(vars.visuals.handsType == 7)
                    return Mp3;
                else if(vars.visuals.handsType == 8)
                    return Random;
                else if(vars.visuals.handsType == 9)
                    return Random1;
                else if(vars.visuals.handsType == 10)
                    return Random2;
                else if(vars.visuals.handsType == 11)
                    return Random3;
            }();
            
            materialCheckFirst->ColorModulate(vars.colors.hands);
            materialCheckFirst->AlphaModulate(vars.visuals.handchams_alpha / 255.f);
            pModelRender->ForcedMaterialOverride(materialCheckFirst);
            CallOriginalModel(thisptr, context, state, pInfo, pCustomBoneToWorld);
        }
        
        // Player Chams
        if(pszModel.find("models/player") != string::npos && vars.visuals.chams)
        {
            auto* local = pEntList->GetClientEntity(pEngine->GetLocalPlayer());
            auto* entity = pEntList->GetClientEntity(pInfo.entity_index);
        
            
            if(entity)
            {
                if(entity->GetHealth() > 0)
                {
                    
                    Color ColorIgnorez = [&]() -> Color
                    {
                        if(entity->GetTeam() == 2)
                            return vars.colors.tchams;
                        else if(entity->GetTeam() == 3)
                            return vars.colors.ctchams;
                        else if(pEngine->GetLocalPlayer() == 3)
                            return vars.colors.ctchams;
                    }();
                    
                    Color ColorNonIgnorez = [&]() -> Color
                    {
                        if(entity->GetTeam() == 2)
                            return vars.colors.tchams_ign;
                        else if(entity->GetTeam() == 3)
                            return vars.colors.ctchams_ign;
                    }();
                    
                    Color FakeLagColor = [&]() -> Color
                    {
                        if(entity->GetTeam() == 2)
                            return vars.colors.fakelag;
                        else if(entity->GetTeam() == 3)
                            return vars.colors.fakelag;
                    }();
                    
                    Color ScopedColors = [&]() -> Color
                    {
                        if(entity->GetTeam() == 2)
                            return vars.colors.scopedchams;
                        else if(entity->GetTeam() == 3)
                            return vars.colors.scopedchams;
                    }();
                    
                    IMaterial* materialCheckFirst = [&]() -> IMaterial*
                    {
                        if(vars.visuals.playersType == 0)
                            return Random4;
                        else if(vars.visuals.playersType == 1)
                            return firstLayer;
                        else if (vars.visuals.playersType == 2)
                            return firstWire;
                        else if(vars.visuals.playersType == 3)
                            return Plastic;
                        else if(vars.visuals.playersType == 4)
                            return Gold;
                        else if(vars.visuals.playersType == 5)
                            return crystal;
                        else if(vars.visuals.playersType == 6)
                            return Glass;
                        else if(vars.visuals.playersType == 7)
                            return Mp3;
                        else if(vars.visuals.playersType == 8)
                            return Random;
                        else if(vars.visuals.playersType == 9)
                            return Random1;
                        else if(vars.visuals.playersType == 10)
                            return Random2;
                        else if(vars.visuals.playersType == 11)
                            return Random3;
                    }();
                    
                    
                    
                    IMaterial* materialCheckSecond = [&]() -> IMaterial*
                    {
                        if(vars.visuals.playersType == 0)
                            return secondLit;
                        else if(vars.visuals.playersType == 1)
                            return secondLayer;
                        else if (vars.visuals.playersType == 2)
                            return secondWire;
                    }();
                    
                    IMaterial* materialFakelag = [&]() -> IMaterial*
                    {
                        if(vars.visuals.fakelagtype == 0)
                            return Random4;
                        else if(vars.visuals.fakelagtype == 1)
                            return firstLayer;
                        else if (vars.visuals.fakelagtype == 2)
                            return firstWire;
                        else if(vars.visuals.fakelagtype == 3)
                            return Plastic;
                        else if(vars.visuals.fakelagtype == 4)
                            return Gold;
                        else if(vars.visuals.fakelagtype == 5)
                            return crystal;
                        else if(vars.visuals.fakelagtype == 6)
                            return Glass;
                        else if(vars.visuals.fakelagtype == 7)
                            return Mp3;
                        else if(vars.visuals.fakelagtype == 8)
                            return Random;
                        else if(vars.visuals.fakelagtype == 9)
                            return Random1;
                        else if(vars.visuals.fakelagtype == 10)
                            return Random2;
                        else if(vars.visuals.fakelagtype == 11)
                            return Random3;
                    }();
                    
                    
                    
                    
                    if (CreateMove::sendPacket == true)
                        local->SetupBones(localfakelagmatrix, 128, BONE_USED_BY_HITBOX, pGlobals->curtime);
                    
                    if (vars.misc.flagchams && vars.misc.thirdperson && local->GetVelocity().Length2D() > 30 && !local->IsScoped())
                    {
                        materialFakelag->AlphaModulate(vars.visuals.fakelagchams_alpha / 255.0f - 0.1);
                        materialFakelag->ColorModulate(FakeLagColor);
                        pModelRender->ForcedMaterialOverride(materialFakelag);
                        CallOriginalModel(thisptr, context, state, pInfo, localfakelagmatrix);
                        pModelRender->ForcedMaterialOverride(nullptr);
                        
                    }
                    if(vars.misc.thirdperson && local->IsScoped() && entity == local) {
                        materialCheckFirst->AlphaModulate(25 / 255.f);
                        materialCheckFirst->ColorModulate(ScopedColors);
                        pModelRender->ForcedMaterialOverride(materialCheckFirst);
                        CallOriginalModel(thisptr, context, state, pInfo, pCustomBoneToWorld);
                        pModelRender->ForcedMaterialOverride(nullptr);
                        return;
                    }
                    if(vars.visuals.enemyonly && local->GetTeam() == entity->GetTeam())
                    {
                        CallOriginalModel(thisptr, context, state, pInfo, pCustomBoneToWorld);
                        pModelRender->ForcedMaterialOverride(NULL);
                    }
                    else
                    {
                        if(!vars.visuals.visonly)
                        {
                            secondLayer->AlphaModulate(vars.visuals.playerchams_alpha / 255.f);
                            secondLayer->ColorModulate(ColorNonIgnorez);
                            pModelRender->ForcedMaterialOverride(secondLayer);
                            CallOriginalModel(thisptr, context, state, pInfo, pCustomBoneToWorld);
                        }
                        
                        materialCheckFirst->ColorModulate(ColorIgnorez);
                        materialCheckFirst->AlphaModulate(vars.visuals.playerchams_alpha / 255.f);
                        pModelRender->ForcedMaterialOverride(materialCheckFirst);
                        CallOriginalModel(thisptr, context, state, pInfo, pCustomBoneToWorld);
                    }
                    
                    
                }
            }
        }
    }
    
    CallOriginalModel(thisptr, context, state, pInfo, pCustomBoneToWorld);
    pModelRender->ForcedMaterialOverride(NULL);
}
