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
