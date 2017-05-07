//
// Created by 王若璇 on 17/5/7.
//

#ifndef MYSTL_ALLOC_H
#define MYSTL_ALLOC_H

#include <cstddef>

namespace MySTL {

    ///@brief 空间配置器,STL二级内存构造
    class Alloc {
    private:
        ///该处使用枚举类型，也可以使用const int 类型
        enum EAlign {
            ///小型区块上调边界
            ALIGN = 8
        };
        const size_t EMaxBytes = 128;
        const int NumFreeList = static_cast<const int>(EMaxBytes / EAlign::ALIGN);
        const int NumObj = 20;


    private:
        ///@brief 将bytes上调为8的倍数
        static size_t ROUND_UP(size_t bytes);

        ///@brief 根据区块大小，决定选择第n号free-list,n从0开始
        static size_t FREELIST_INDEX(size_t bytes);

        ///@brief 返回一个大小为n的对象，并可能加入大小为n的其他区块到free-list
        static void* refill(size_t n);

        ///@brief 内存池新配置一段空间
        ///@param size 区块大小\
        ///       num  区块数量
        static char *chunk_alloc(size_t size,size_t& num);

    public:

        ///@brief 公开空间配置器接口
        static void *allocate(size_t bytes);

        ///@brief 释放内存
        static void deallocate(void *ptr,size_t bytes);

        ///@brief 重新配置内存
        static void *reallocate(void *ptr,size_t old_sz,size_t new_sz);

    };
}


#endif //MYSTL_ALLOC_H
