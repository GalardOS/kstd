#pragma once

#include "common.hh"

/*
 * TODOs:
 *    - add mutex to refcount control block if multithreading is added.
 *    - templated allocation to internal pointer allocation (reference -> std::make_shared)
 */

namespace kstd {


    template<typename type>
    class ptr {
    public: 
        /*
         * Assings the pointer and initializes the process
         * controll block.
         * 
         * param newed: allocated pointer
         */
        static ptr<type> allocate(type* newed) {
            ptr<type> result;

            // Assing the pointer
            result.pointer = newed;

            // Create a new control block and set the refcount to 1
            result.control_block = new refcount_control;
            result.control_block->num_references = 1;

            std::cout << "Allocated" << std::endl;

            return result;
        }

        /*
         * Default constructor of this class. Very important to know
         * that this constructor does not allocate anything. Allocation 
         * should be done with ptr::allocate.
         */
        ptr() 
            : allocated(false),
              control_block(nullptr),
              pointer(nullptr) {

        }

        /*
         * Copy constructor of this class. Increases the reference count 
         * and references copied control block.
         */
        ptr(const ptr<type>& cpy) {
            // Point the control block to the copied one and
            // increase the reference count
            control_block = cpy.control_block;
            control_block->num_references++;

            // Copy the pointer 
            pointer = cpy.pointer;

            allocated = true;

            std::cout << "Copy created: " << control_block->num_references << std::endl;
        }

        void operator=(const ptr<type>& cpy) {
            // Point the control block to the copied one and
            // increase the reference count
            control_block = cpy.control_block;
            control_block->num_references++;

            // Copy the pointer 
            pointer = cpy.pointer;

            allocated = true;

            std::cout << "Copy created: " << control_block->num_references << std::endl;
        }

        /*
         * Destructor of the class. This functions frees all resources if
         * pointer is no longer referenced.
         */
        ~ptr() {
            // If the control block is nullptr there is no need
            // to free any memory neither reduce the reference count
            if(control_block != nullptr) {

                // Decrease the number of references
                control_block->num_references--;
            
                std::cout << "Dealocating, now " << control_block->num_references << " references\n";
                
                // If this pointer is no longer referenced
                // delete the control block and pointer itself
                if(control_block->num_references == 0) {
                    delete control_block;
                    delete pointer;
                }
            }
        }

        /*
         * Retunrs the raw pointer.
         */
        type* raw() const { return pointer; }

        /*
         * Returns if the pointer is actually allocated.
         * 
         * return: true if allocated, false if not
         */
        bool is_allocated() { return allocated; }
    private:
        struct refcount_control {
            uint16 num_references;
        }* control_block;

        type* pointer;

        bool allocated;
    protected:
    };
}