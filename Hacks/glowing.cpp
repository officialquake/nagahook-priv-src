//
//  glowing.cpp
//  vHook
//
//  Created by Timothy Dillan on 31/8/19.
//  Copyright © 2019 ViKiNG. All rights reserved.
//

#include "glowing.hpp"
/*std::vector<std::pair<int, int>> custom_glow_entities;


void CustomGlow::FrameStageNotify(ClientFrameStage_t stage)
{
    for (int i = 64; pEntList->GetHighestEntityIndex(); i++)
    {
        C_BaseEntity* entity = pEntList->GetClientEntity(i);
        if(pEngine->IsInGame() && entity && entity->GetClientClass()->m_ClassID == EClassIds::CBaseAnimating)
        {
            if(!glowManager->HasGlowEffect(entity))
            {
                int array_index = glowManager->RegisterGlowObject(entity);
                
                if(array_index != -1)
                    custom_glow_entities.emplace_back(i, array_index);
            }
        }
        else
        {
            auto iterator = std::find_if(custom_glow_entities.begin(), custom_glow_entities.end(),
                                         [&] (const std::pair<int, int>& p) {
                                             return p.first == i;
                                         }
                                         );
            if(iterator != custom_glow_entities.end())
            {
                glowManager->UnregisterGlowObject(iterator->second);
                custom_glow_entities.erase(iterator);
            }
        }
    }
}
*/
