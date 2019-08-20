#include <vector>
#include <cstdint>
#include "../SDK/Others.h"
#include "../SDK/GameEvent.h"
#include "../Hacks/logshots.hpp"

namespace Resolver
{
    extern std::vector<int64_t> Players;
    
    //Hooks
    void FrameStageNotify(ClientFrameStage_t stage , C_BaseEntity* entity);
    void PostFrameStageNotify(ClientFrameStage_t stage);
}


namespace Resolver1
{
    extern std::vector<int64_t> Players1;
    
    //Hooks
    void FrameStageNotify1(ClientFrameStage_t stage , C_BaseEntity* entity);
    void PostFrameStageNotify1(ClientFrameStage_t stage);
}
