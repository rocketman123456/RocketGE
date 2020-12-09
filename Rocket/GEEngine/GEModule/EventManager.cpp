#include "GEModule/EventManager.h"

namespace Rocket {
    EventManager* g_EventManager = new EventManager();

    int EventManager::Initialize()
    {
        return 0;
    }

    void EventManager::Finalize()
    {

    }

    void EventManager::Tick(Timestep ts)
    {

    }

    void EventManager::OnEvent(Event& event)
    {

    }
}