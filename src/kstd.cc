#include "kstd.hh"
#include "memory/heap.hh"

namespace kstd {
    void ___initialize(const ___initialization_params& params) {
        // Initialize the heap 
        ___heap_params hparams {
            .heap_start = params.heap_start,
            .heap_size = params.heap_size
        };
        ___heap_initialize(static_cast<uint32*>(params.heap_start), params.heap_size);
    }
}