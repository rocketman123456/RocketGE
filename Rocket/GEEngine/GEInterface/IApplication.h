#pragma once
#include "GEInterface/IRuntimeModule.h"
#include "GEEvent/Event.h"

namespace Rocket {
    Interface IApplication : implements IRuntimeModule
    {
    public:
        virtual int Initialize() = 0;
        virtual void Finalize() = 0;
        // One cycle of the main loop
        virtual void Tick(Timestep ts) = 0;
        virtual void OnEvent(Event& event) = 0;

        virtual bool IsQuit() = 0;
    };

    IApplication* CreateApplicationInstance();
}