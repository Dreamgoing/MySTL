//
// Created by 王若璇 on 17/5/7.
//

#include "Alloc.h"

char* MySTL::Alloc::start_free = 0;
char* MySTL::Alloc::end_free = 0;
size_t MySTL::Alloc::heap_size = 0;

MySTL::Alloc::obj* free_list[] ={
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

size_t MySTL::Alloc::ROUND_UP(size_t bytes) {
    return (bytes+EAlign::ALIGN-1)& ~(EAlign::ALIGN-1);
}

size_t MySTL::Alloc::FREELIST_INDEX(size_t bytes) {
    return (bytes+EAlign::ALIGN-1)/EAlign::ALIGN-1;
}


void *MySTL::Alloc::refill(size_t n) {
    ///@param n为8的倍数

    return nullptr;
}

char *MySTL::Alloc::chunk_alloc(size_t bytes, size_t &nodjs) {
    ///@param bytes 为8的倍数

    char *result = 0;

    ///总需内存
    size_t total_bytes = nodjs*bytes;
    ///内存池剩余空间
    size_t bytes_left = end_free-start_free;
    if(bytes_left>=total_bytes){
        ///若剩余空间完全满足需求量，则返回剩余空间
        result = start_free;
        start_free+=total_bytes;
        return result;
    }else if(bytes_left>=bytes){
        ///内存池剩余空间不能完全满足需求量，但足够供应一个(含)以上的区块
        ///修改所能提供区块个数
        nodjs = bytes_left/bytes;
        total_bytes = bytes*nodjs;
        result = start_free;
        start_free+=total_bytes;
        return result;
    } else{
        ///内存池剩余空间连一个区块的大小都无法提供
        size_t  bytes_to_get = 2*total_bytes+ROUND_UP(heap_size>>4);

        ///以下试着让内存池中的残余零头还有价值
        if(bytes_left>0){
            ///内存池内还有一些零头，先配给适当的free list
            ///首先找到适当的free_list
        }
    }
}

void *MySTL::Alloc::allocate(size_t bytes) {
    if(bytes> static_cast<size_t >(EMaxBytes::MAXBYTES)){
        ///大于128就调用第一级配置器
        return malloc(bytes);
    } else{
        ///获取特定free_list的index
        size_t index = FREELIST_INDEX(bytes);

        obj* list = free_list[index];
        if(list){
            ///若当前特点free_list还有空间剩余则从中取出
            free_list[index] = free_list[index]->next;
            return list;
        } else{
            ///此list没有足够的空间，需要从内存池中取出内存
            ///获取上调为8的倍数内存
            return refill(ROUND_UP(bytes));
        }

    }
}

void MySTL::Alloc::deallocate(void *ptr, size_t bytes) {

}

void *MySTL::Alloc::reallocate(void *ptr, size_t old_sz, size_t new_sz) {
    return nullptr;
}
