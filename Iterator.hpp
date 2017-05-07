//
// Created by 王若璇 on 17/5/7.
//

#ifndef MYSTL_ITERATOR_HPP
#define MYSTL_ITERATOR_HPP

#include <stddef.h>

///@brief 迭代器的设计与萃取实践
namespace MySTL{

    ///@brief iterator_category 根据移动特性与施行操作，迭代器被分为五类：
    struct input_iterator_tag{};
    struct output_iterator_tag{};
    struct forward_iterator_tag:public input_iterator_tag{};
    struct bidirectional_iterator_tag:public forward_iterator_tag{};
    struct random_access_iterator_tag:public bidirectional_iterator_tag{};

    template <class T,class Distance>
    struct input_iterator{
        typedef input_iterator_tag iterator_category;
        typedef T value_type;
        typedef Distance difference_type;
        typedef T* pointer;
        typedef T& reference;
    };


    template <class Category,class T,class Distance=ptrdiff_t , class Pointer = T*,class Reference = T&>
    struct iterator{
        typedef Category	iterator_category;
        typedef T			value_type;
        typedef Distance	difference_type;
        typedef Pointer		pointer;
        typedef Reference	reference;
    };


    template <class Iterator>
    struct iterator_traits
    {
        typedef typename Iterator::iterator_category	iterator_category;
        typedef typename Iterator::value_type			value_type;
        typedef typename Iterator::difference_type		difference_type;
        typedef typename Iterator::pointer				pointer;
        typedef typename Iterator::reference 			reference;
    };

}

#endif //MYSTL_ITERATOR_HPP
