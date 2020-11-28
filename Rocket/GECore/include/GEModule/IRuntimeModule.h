#pragma once
#include "GECore/Core.h"

namespace Rocket {
    Interface IRuntimeModule{
    public:
        virtual ~IRuntimeModule() {};

        virtual int Initialize() = 0;
        virtual void Finalize() = 0;

        virtual void Tick() = 0;
    };
}