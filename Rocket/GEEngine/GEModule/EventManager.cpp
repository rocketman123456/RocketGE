#include "GEModule/EventManager.h"

namespace Rocket
{
    EventManager *g_EventManager = new EventManager();

    int EventManager::Initialize()
    {
        return 0;
    }

    void EventManager::Finalize()
    {
    }

    int EventManager::Tick(Timestep ts)
    {
        return 0;
    }

    void EventManager::OnEvent(Event &event)
    {
    }
} // namespace Rocket