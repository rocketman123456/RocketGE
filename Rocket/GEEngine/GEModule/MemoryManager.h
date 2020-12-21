#pragma once
#include "GEInterface/IMemoryManager.h"
#include "GEUtils/Portable.h"
#include "GECore/Core.h"

namespace Rocket {
    ENUM(MemoryType)
    {
        CPU = "CPU"_i32,
        GPU = "GPU"_i32
    };

    std::ostream& operator<< (std::ostream& out, MemoryType type);

    class MemoryManager : implements IMemoryManager
    {
    public:
        ~MemoryManager() override = default;

        int Initialize() override;
        void Finalize() override;
        int Tick(Timestep ts) override;

        void* AllocatePage(size_t size) override;
        void  FreePage(void* p) override;

    protected:
        struct MemoryAllocationInfo 
        {
            size_t PageSize;
            MemoryType PageMemoryType;
        };

        std::map<void*, MemoryAllocationInfo> m_mapMemoryAllocationInfo;
    };
}

