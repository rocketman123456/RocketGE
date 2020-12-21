#include "GEModule/MemoryManager.h"

using namespace Rocket;
using namespace std;

namespace Rocket
{
    std::ostream &operator<<(std::ostream &out, MemoryType type)
    {
        auto n = static_cast<int32_t>(type);
        n = endian_net_unsigned_int<int32_t>(n);
        char *c = reinterpret_cast<char *>(&n);

        for (size_t i = 0; i < sizeof(int32_t); i++)
        {
            out << *c++;
        }

        return out;
    }
} // namespace Rocket

int MemoryManager::Initialize()
{
    return 0;
}

void MemoryManager::Finalize()
{
    assert(m_mapMemoryAllocationInfo.empty());
}

int MemoryManager::Tick(Timestep ts)
{
#if DEBUG
    static int count = 0;

    if (count++ == 3600)
    {
        for (auto info : m_mapMemoryAllocationInfo)
        {
            cerr << info.first << '\t';
            cerr << info.second.PageMemoryType;
            cerr << info.second.PageSize;
        }
    }
#endif
    return 0;
}

void *MemoryManager::AllocatePage(size_t size)
{
    uint8_t *p;

    p = static_cast<uint8_t *>(malloc(size));
    if (p)
    {
        MemoryAllocationInfo info = {size, MemoryType::CPU};
        m_mapMemoryAllocationInfo.insert({p, info});
    }

    return static_cast<void *>(p);
}

void MemoryManager::FreePage(void *p)
{
    auto it = m_mapMemoryAllocationInfo.find(p);
    if (it != m_mapMemoryAllocationInfo.end())
    {
        m_mapMemoryAllocationInfo.erase(it);
        free(p);
    }
}
