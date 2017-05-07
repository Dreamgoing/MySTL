//
// Created by 王若璇 on 17/5/7.
//

#ifndef MYSTL_ALLOC_H
#define MYSTL_ALLOC_H

#include <cstddef>
#include <cstdlib>

namespace MySTL {

    ///@brief 空间配置器,STL二级内存构造，内存池的方式管理内存为次级配置(sub-allocation)
    class Alloc {
    private:
        ///该处使用枚举类型，也可以使用const int 类型
        enum EAlign {
            ///小型区块上调边界
            ALIGN = 8
        };
        enum ENFreeLists{NUMFREE_LIST=16};
        ///@note 枚举类型可以被静态函数所使用
        enum EMaxBytes{MAXBYTES=128};

        enum ENObjs{NOBJS=20};
//        const size_t EMaxBytes = 128;
    public:
        ///free-list 节点的构造
        union obj{
            obj *next;
            char client[1];
        };
    private:
//        const int NumFreeList = static_cast<const int>(EMaxBytes / EAlign::ALIGN);
//        const int NumObj = 20;

        ///16个free-list \
        /// @details 大小依次为8,16,24,...,128
        static obj* free_list[ENFreeLists::NUMFREE_LIST];

        ///@note 仅在chunk_alloc()中变化
        static char *start_free; ///内存池起始位置
        static char *end_free;   ///内存池结束位置
        static size_t heap_size;
    private:
        ///@brief 将bytes上调为8的倍数
        inline static size_t ROUND_UP(size_t bytes);

        ///@brief 根据区块大小，决定选择第n号free-list,n从0开始
        inline static size_t FREELIST_INDEX(size_t bytes);

        ///@brief 返回一个大小为n的对象，并可能加入大小为n的其他区块到free-list
        static void* refill(size_t n);

        ///@brief 内存池新配置一段空间
        ///@param size 区块大小,已经保证了为8的倍数\
        ///       num  区块数量,用来获得最终分配了多少块
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
