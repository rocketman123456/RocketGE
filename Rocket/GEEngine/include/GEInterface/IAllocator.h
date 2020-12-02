#pragma once
#include "GECore/Core.h"
#include <cstdint>
#include <cstdlib>

namespace Rocket {
    Interface IAllocator {
    public:
        // debug patterns
        const uint8_t PATTERN_ALIGN = 0xFC;
        const uint8_t PATTERN_ALLOC = 0xFD;
        const uint8_t PATTERN_FREE  = 0xFE;

        virtual ~IAllocator(); 

        virtual void* Allocate(size_t size) = 0;
        virtual void  Free(void* p) = 0;
        virtual void  FreeAll() = 0;
    };
}