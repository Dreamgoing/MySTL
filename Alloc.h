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

        static void* refill(size_t n);


    };
}


#endif //MYSTL_ALLOC_H
