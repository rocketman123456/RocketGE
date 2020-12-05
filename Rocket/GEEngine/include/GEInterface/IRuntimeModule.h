#pragma once
#include "GECore/Core.h"
#include "GEEvent/Event.h"
#include "GEUtils/Timestep.h"

namespace Rocket {
    // TODO : change all part of program into modules
    Interface IRuntimeModule{
    public:
        virtual ~IRuntimeModule() {};

        virtual int Initialize() = 0;
        virtual void Finalize() = 0;

        virtual void Tick(Timestep ts) = 0;
        virtual void OnEvent(Event& event) {}

        // For debug
        virtual const std::string& GetName() const { return m_Name; }
    protected:
        std::string m_Name = "IRuntimeModule";
    };
}
