#pragma once
#include "GEInterface/IAllocator.h"
#include <cstddef>
#include <cstdint>

namespace Rocket
{
    struct BlockHeader
    {
        // union-ed with data
        BlockHeader *pNext;
    };

    struct PageHeader
    {
        PageHeader *pNext;
        BlockHeader *Blocks()
        {
            return reinterpret_cast<BlockHeader *>(this + 1);
        }
    };

    class BlockAllocator : implements IAllocator
    {
    public:
        BlockAllocator();
        BlockAllocator(size_t data_size, size_t page_size, size_t alignment);
        ~BlockAllocator() override;
        // disable copy & assignment
        BlockAllocator(const BlockAllocator &clone) = delete;
        BlockAllocator &operator=(const BlockAllocator &rhs) = delete;

        // resets the allocator to a new configuration
        void Reset(size_t data_size, size_t page_size, size_t alignment);

        // alloc and free blocks
        void *Allocate();
        void *Allocate(size_t size) override;
        void Free(void *p) override;
        void FreeAll() override;

    private:
#if defined(RK_DEBUG)
        // fill a free page with debug patterns
        void FillFreePage(PageHeader *pPage);

        // fill a block with debug patterns
        void FillFreeBlock(BlockHeader *pBlock);

        // fill an allocated block with debug patterns
        void FillAllocatedBlock(BlockHeader *pBlock);
#endif
        // gets the next block
        BlockHeader *NextBlock(BlockHeader *pBlock);

        // the page list
        PageHeader *m_pPageList;

        // the free block list
        BlockHeader *m_pFreeList;

        size_t m_szPageSize;
        size_t m_szAlignmentSize;
        size_t m_szBlockSize;
        size_t m_nBlocksPerPage;

        // statistics
        size_t m_nPages;
        size_t m_nBlocks;
        size_t m_nFreeBlocks;
    };
} // namespace Rocket
