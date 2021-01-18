#pragma once 

#include "common.hh"

namespace kstd {
    void ___heap_initialize(uint64* buffer, uint32 size);

    void* alloc(uint32 size);
    void  free(void* ptr);
}