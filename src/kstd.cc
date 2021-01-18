#include "kstd.hh"
#include "memory/heap.hh"

namespace kstd {
    void ___initialize(const ___initialization_params& params) {
        ___heap_initialize(static_cast<uint64*>(params.heap_start), params.heap_size);
    }
}