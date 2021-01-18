#include <iostream>

#include "kstd.hh"
#include "memory/ptr.hh"

#define TEST(fn) std::cout << "[+] " << #fn << std::endl; if(!(fn())) { std::cout << "[ERR] Something went wrong on the test\n"; } std::exit(-1)

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

bool container_test() {
    return true;
}

int main(int argc, char** argv) {
    kstd::___initialization_params params;

    kstd::___initialize(params);


    TEST(smartptr_test);
}