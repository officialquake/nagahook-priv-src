#include "main.h"
#include "Hacks/hitmarker.h"

 class EventListener : public IGameEventListener2
 {
 public:
 EventListener(std::vector<const char*> events)
 {
 for (auto& it : events)
 pGameEventManager->AddListener(this, it, false);
 }
 
 ~EventListener()
 {
 pGameEventManager->RemoveListener(this);
 }
 
void FireGameEvent(IGameEvent* event)
 {
     Hitmarkers::FireGameEvent(event);
 }
 
        int GetEventDebugID() override
     {
         return 42;
     }
 };
