#pragma once
#include "GEInterface/IRuntimeModule.h"
#include "GEEvent/Event.h"

namespace Rocket
{
    Interface IApplication : implements IRuntimeModule
    {
    public:
        IApplication(const std::string &name = "IApplication") : IRuntimeModule(name) {}
        virtual ~IApplication() = default;

        virtual void PreInitialize() = 0;
        virtual int Initialize() override = 0;
        virtual void PostInitialize() = 0;
        virtual void Finalize() override = 0;

        virtual void PreInitializeModule() = 0;
        virtual int InitializeModule() = 0;
        virtual void PostInitializeModule() = 0;
        virtual void FinalizeModule() = 0;

        virtual void TickModule() = 0;
        virtual void Tick() = 0;

        virtual int Tick(Timestep ts) override { return 0; }
        virtual void OnEvent(Event & event) override = 0;

        virtual bool GetIsRunning() = 0;
    };

    IApplication *CreateApplicationInstance();
} // namespace Rocket