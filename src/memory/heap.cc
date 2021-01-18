#include "heap.hh"

#define BLOCK_DEFINE_OCUP(size)         ((size) | BIT(31))
#define BLOCK_DEFINE_EMPTY(size)        ((size) & (~BIT(31)))
#define BLOCK_GET_AVAILABLE(x)          (((x) >> 31) & 1)
#define BLOCK_GET_SIZE(x)               ((x) & 0xEFFFFFFF)

namespace kstd {

    static uint32* memory_buffer;   // Pointer to heap buffer
    static uint32  memory_size;     // Size in 32bit words

    void ___heap_initialize(uint32* buffer, uint32 size) {
        // Setup heap start and size
        memory_buffer = buffer;
        memory_size = size / 4;

        // Set the first meta block to free (highest bit is 0)
        memory_buffer[0] = 0;
    }

    void* heap_allocate(uint32 size) {
        uint32 idx_size = size / 8;
        
        bool space_found = false;
        
        uint32 block = 0;
        while(!space_found) {
            uint32& block_meta = memory_buffer[block];

            // If the block is free check if fits, if fits update
            // the meta block and return the pointer
            if(BLOCK_GET_AVAILABLE(block_meta) == 0) {
                uint32 available_size = block_meta & 0xEFFFFFFF;

                // If there is not enough space jump go find another
                // empty block
                if(size > available_size) {
                    block += available_size + 1;
                    continue;
                }

                uint32 new_empty_size = available_size - (size + 1);
                memory_buffer[block + size + 1] = BLOCK_DEFINE_EMPTY(new_empty_size);

                // Set block as ocupied and return pointer
                block_meta = BLOCK_DEFINE_OCUP(size);
                
                return memory_buffer + block + 1;
            }
        }
    }

    void heap_deallocate(void* ptr) {
        uint32* casted_pointer = static_cast<uint32*>(ptr);
        uint32 index = memory_buffer - casted_pointer;

        uint32& meta_block = memory_buffer[index - 1];
        uint32 size = BLOCK_GET_SIZE(meta_block);

        meta_block = BLOCK_DEFINE_EMPTY(size);
    }
}