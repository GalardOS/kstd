#pragma once

namespace kstd {
    struct ___initialization_params {
        // Heap related information
        void* heap_start;
        uint64 heap_size;
    };

    void ___initialize(const ___initialization_params& params);
}