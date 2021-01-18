#pragma once

#include "common.hh"

namespace kstd {
    struct ___initialization_params {
        // Heap related information
        void* heap_start;
        uint32 heap_size;
    };

    void ___initialize(const ___initialization_params& params);
}