#pragma once
#include "GECore/Core.h"
#include "GEEvent/Event.h"
#include "GEUtils/Timestep.h"

namespace Rocket
{
    // TODO : change all basic part of program into modules
    Interface IRuntimeModule
    {
    public:
        IRuntimeModule(const std::string &name = "IRuntimeModule") : m_Name(name) {}
        virtual ~IRuntimeModule(){};

        virtual int Initialize() = 0;
        virtual void Finalize() = 0;

        virtual int Tick(Timestep ts) = 0;
        virtual void OnEvent(Event & event) {}

        // For debug
        const std::string &GetName() const { return m_Name; }

    private:
        std::string m_Name;
    };
} // namespace Rocket
