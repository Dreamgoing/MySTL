//
// Created by 王若璇 on 17/5/7.
//

#include "Alloc.h"

size_t MySTL::Alloc::ROUND_UP(size_t bytes) {
    return 0;
}

size_t MySTL::Alloc::FREELIST_INDEX(size_t bytes) {
    return 0;
}

void *MySTL::Alloc::refill(size_t n) {
    return nullptr;
}

char *MySTL::Alloc::chunk_alloc(size_t size, size_t &nodjs) {
    return nullptr;
}

void *MySTL::Alloc::allocate(size_t bytes) {
    return nullptr;
}

void MySTL::Alloc::deallocate(void *ptr, size_t bytes) {

}

void *MySTL::Alloc::reallocate(void *ptr, size_t old_sz, size_t new_sz) {
    return nullptr;
}
