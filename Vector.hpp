//
// Created by 王若璇 on 17/5/8.
//

#ifndef MYSTL_VECTOR_HPP
#define MYSTL_VECTOR_HPP

#include "Alloc.h"
namespace MySTL{
    template <class T,class alloc=Alloc>
    class Vector{
    public:
        typedef T                           value_type;
        typedef value_type*                 pointer;
        typedef value_type*                 iterator;
        typedef value_type&                 reference;
        typedef size_t                      size_type;
        typedef ptrdiff_t                   difference_type;
    };
}

#endif //MYSTL_VECTOR_HPP
