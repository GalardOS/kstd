#pragma once 

#include "common.hh"

namespace kstd {
    struct ___heap_params {
        void* heap_start;
        uint32 heap_size;
    };

    void ___heap_initialize(const ___heap_params& params);

    void* heap_allocate(uint32 size);
    void heap_deallocate(void* ptr);
}