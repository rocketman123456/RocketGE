#pragma once
#include "GECore/Core.h"
#include "GEEvent/Event.h"

namespace Rocket {
    Interface IRuntimeModule{
    public:
        virtual ~IRuntimeModule() {};

        virtual int Initialize() = 0;
        virtual void Finalize() = 0;

        virtual void Tick() = 0;
    };
}
