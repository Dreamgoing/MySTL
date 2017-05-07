//
// Created by 王若璇 on 17/5/7.
//

#ifndef MYSTL_ALLOCATOR_HPP
#define MYSTL_ALLOCATOR_HPP

#include <cstddef>
#include <new>
#include <iostream>
#include <cstdlib>

namespace MySTL {
    ///@brief 空间配置器

    template<class T>
    inline T *allocate(ptrdiff_t size, T *) {
//        std::set_new_handler(0);

        ///@return 分配的空间

//        std::cout<<(size_t)size*(sizeof(T))<<std::endl;
        T* tmp = static_cast<T*>(::operator new((size_t)(size* sizeof(T))));
//        std::cout<< sizeof(tmp)<<std::endl;
        if(tmp==0){
            std::cerr<<"out of memory"<<std::endl;
        }
        return tmp;
    }
    template <class T>
    inline void deallocate(T* buffer){
        ::operator delete(buffer);
    }

    template <class T>
    class Allocator{
    public:

        ///@brief type definition
        typedef T value_type;
        typedef T* pointer;
        typedef const T* const_pointer;
        typedef T& reference;
        typedef const T& const_reference;
        typedef size_t  size_type;
        typedef ptrdiff_t difference_type;


        static pointer allocate(size_type n){
//            std::cerr<<(difference_type)n<<std::endl;
            return MySTL::allocate(static_cast<difference_type >(n), reinterpret_cast<pointer >(0));
        }

        static void deallocate(pointer p){
            MySTL::deallocate(p);
        }

        static pointer address(reference x){
            return static_cast<pointer >(&x);
        }
        static const_pointer const_address(const_reference x){
            return static_cast<const_reference >(&x);
        }


    };

}





#endif //MYSTL_ALLOCATOR_HPP
