#pragma once

#include "common.hh"
#include <array>

namespace kstd {
    template<typename type, uint32 size>
    class array {
    public:
        array(const type* arr, uint32 arr_size) {
            uint32 smallest_size = arr_size ? (arr_size < size) : size; 

            for(int i = 0; i < smallest_size; i++) {
                data[i] = arr[i];
            }
        }

        ~array() = default;

        type& operator[](uint32 index) {
            /// TODO: bounds checking if debug is enabled

            return data[index];
        }
        
        type operator[](uint32 index) const {
            /// TODO: bounds checking if debug is enabled
            
            return data[index];
        }

        constexpr uint32 size() const { 
            return size;
        }
    private:
        type data[size];
    protected:
    };
}