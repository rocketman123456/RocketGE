#pragma once
#include "GEInterface/IRuntimeModule.h"
#include <cstddef>

namespace Rocket {
    Interface IMemoryManager : inheritance IRuntimeModule
    {
    public:
        int Initialize() override = 0;
        void Finalize() override = 0;
        int Tick(Timestep ts) override = 0;

        virtual void* AllocatePage(size_t size) = 0;
        virtual void  FreePage(void* p) = 0;
    };

    extern IMemoryManager*   g_pMemoryManager;
}