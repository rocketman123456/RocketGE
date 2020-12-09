#pragma once
#include "GEInterface/IRuntimeModule.h"

namespace Rocket {
    class EventManager : implements IRuntimeModule
    {
    public:
        EventManager() : IRuntimeModule("EventManager") {}
        virtual ~EventManager() = default;

        virtual int Initialize() override;
        virtual void Finalize() override;

        virtual void Tick(Timestep ts) override;
        virtual void OnEvent(Event& event) override;
    };

    extern EventManager* g_EventManager;
}