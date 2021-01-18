#include <iostream>

#include "kstd.hh"
#include "memory/ptr.hh"
#include "memory/heap.hh"

#define TEST(fn) std::cout << "[+] " << #fn << std::endl; if(!(fn())) { std::cout << "[ERR] Something went wrong on the test\n"; }

bool smartptr_test() {
    kstd::ptr<int> intprt; 

    std::cout << "Is allocated? " << intprt.is_allocated() << std::endl;

    intprt = kstd::ptr<int>::allocate(new int);

    std::cout << "Is now allocated? " << intprt.is_allocated() << std::endl;

    {
        kstd::ptr<int> reference = intprt;
    }

    return true;
}

bool malloc_test() {
    std::cout << "Allocating variable a\n";
    void* a = kstd::alloc(2 * sizeof(uint64));
    
    std::cout << "Allocating variable b\n";
    void* b = kstd::alloc(sizeof(uint64));

    std::cout << "freeing variable a\n";
    kstd::free(a);

    std::cout << "Allocating variable a\n";
    a = kstd::alloc(sizeof(uint64));

    return true;
}

bool container_test() {
    return true;
}

constexpr uint32 HEAP_SIZE = 15 * 4 * 1024;

int main(int argc, char** argv) {
    kstd::___initialization_params params {
        .heap_start = std::malloc(HEAP_SIZE),
        .heap_size = HEAP_SIZE
    };

    kstd::___initialize(params);


    TEST(smartptr_test);
    TEST(malloc_test);
}