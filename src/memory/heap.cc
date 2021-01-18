#include "heap.hh"
#include <iostream>

#define DEBUG(x) std::cout << x << std::endl;

namespace kstd {
    struct meta_block {
        uint32 size_in_blocks;
        uint32 status;
    }__attribute__((packed));

    static uint64* memory_buffer;   // Pointer to heap buffer
    static uint32  memory_size;     // Size in 32bit words

    void ___heap_initialize(uint64* buffer, uint32 size) {
        // Setup heap start and size
        memory_buffer = buffer;
        memory_size = size / 8;

        // Set the first meta block to free (highest bit is 0)
        ((meta_block*)(memory_buffer))->size_in_blocks = memory_size;
        ((meta_block*)(memory_buffer))->status = 0;
    }

    void* alloc(uint32 size) {
        uint32 index = 0;
        uint32 size_in_blocks = size / 8;

        DEBUG("Allocating " << size_in_blocks << " blocks of memory");

        while(true) {
            DEBUG("Index = " << index);
            
            meta_block* meta = (meta_block*)(memory_buffer + index);

            DEBUG("  size = " << meta->size_in_blocks);
            DEBUG("  free = " << meta->status);

            if(meta->status == 0 && meta->size_in_blocks > size) {
                DEBUG("Block is free");
                
                // Update the free control block to full
                ((meta_block*)(memory_buffer + index))->size_in_blocks = size_in_blocks;
                ((meta_block*)(memory_buffer + index))->status = 1;
                
                // Set the next empty node
                ((meta_block*)(memory_buffer + index + size_in_blocks + 1))->size_in_blocks = memory_size - size_in_blocks - 1;
                ((meta_block*)(memory_buffer + index + size_in_blocks + 1))->status = 0;
                
                return memory_buffer + index + 1;
            } else {
                index += meta->size_in_blocks + 1;
                DEBUG("Not free, next index to search : " << index);
            }
        }

        return nullptr;
    }

    void free(void* ptr) {
        // Point to the control block
        meta_block* control_block = static_cast<meta_block*>(ptr);
        control_block--;

        control_block->status = 0;
    }
}