#pragma once
#include "GEInterface/IRuntimeModule.h"
#include "GEEvent/Event.h"

namespace Rocket {
    Interface IApplication : implements IRuntimeModule
    {
    public:
        virtual void PreInitialize() = 0;
        virtual int Initialize() = 0;
        virtual void PostInitialize() = 0;
        virtual void Finalize() = 0;

        virtual void PreInitializeModule() = 0;
        virtual int InitializeModule() = 0;
        virtual void PostInitializeModule() = 0;
        virtual void FinalizeModule() = 0;

        virtual void TickModule() = 0;
        virtual void Tick() = 0;

        virtual void Tick(Timestep ts) = 0;
        virtual void OnEvent(Event& event) = 0;

        virtual bool GetIsRunning() = 0;
    };

    IApplication* CreateApplicationInstance();
}