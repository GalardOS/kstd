#include <iostream>

#include "kstd.hh"

#define TEST(fn) std::cout << "[+] " << ##fn << std::endl; if(!(fn())) { std::cout << "Something went wrong on the test\n"; } std::exit();

bool container_test() {

}

int main(int argc, char** argv) {
    kstd::___initialization_params params;

    kstd::___initialize(params);


    if(!container_test()) {
        std::cerr << "[ERR] Container test failed\n";
    }
}