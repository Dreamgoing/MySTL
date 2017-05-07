//
// Created by 王若璇 on 17/5/7.
//

#include "Alloc.h"

char* MySTL::Alloc::start_free = 0;
char* MySTL::Alloc::end_free = 0;
size_t MySTL::Alloc::heap_size = 0;

MySTL::Alloc::obj* MySTL::Alloc::free_list[ENFreeLists::NUMFREE_LIST] ={
        0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};

size_t MySTL::Alloc::ROUND_UP(size_t bytes) {
    return (bytes+EAlign::ALIGN-1)& ~(EAlign::ALIGN-1);
}

size_t MySTL::Alloc::FREELIST_INDEX(size_t bytes) {
    return (bytes+EAlign::ALIGN-1)/EAlign::ALIGN-1;
}


void *MySTL::Alloc::refill(size_t bytes) {
    ///@param bytes为8的倍数

    ///nodjs 为预置新增节点的个数
    size_t nodjs = ENObjs::NOBJS ;

    char* chunk = chunk_alloc(bytes,nodjs);
    obj **my_free_list = 0;
    obj *result;
    obj *current_obj = 0,*next_obj = 0;
    if(nodjs==1){
        ///取出的内存只够一个对象使用，free_list无新节点，则直接返回获得的内存
        return chunk;
    } else{
        ///调整free_list，纳入新节点
        my_free_list = free_list+FREELIST_INDEX(bytes);

        ///最终结果内存，返回给客户端
        result = (obj*)(chunk);

        *my_free_list = next_obj = (obj*)(chunk+bytes);

        ///以下将free_list的各个节点串接起来
        for(int i = 1;;i++){
            ///第0个返回给客户端
            current_obj = next_obj;
            next_obj = (obj*)((char*)next_obj+bytes);
            if(nodjs-1==i){
                ///将所有获得的区块放入free_list
                current_obj = 0;
                break;
            } else{

                ///拼接
                current_obj->next = next_obj;
            }

        }
        return result;
    }


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
            obj** my_free_list = free_list+FREELIST_INDEX(bytes_left);

            ///调整free_list，将内存池中的残余空间编入
            ///@note 感觉容易出bug,也可以分开写
            ((obj*)start_free)->next = *my_free_list;
            *my_free_list = (obj*)start_free;
        }

        ///配置heap空间，用来补充内存池
        start_free = (char*)malloc(bytes_to_get);

        if(0==start_free){
            ///heap 空间不足，malloc()分配失败
            obj **my_free_list = 0,*p = 0;
            for(int i =0;i<EMaxBytes::MAXBYTES;i+=EAlign::ALIGN){
                ///调整free_list以释放出未用区块
                my_free_list = free_list+FREELIST_INDEX(i);
                p = *my_free_list;
                if(0!=p){
                    ///free_list内尚有未用区块
                    ///调整free_list以释出未用区块
                    *my_free_list = p->next;
                    ///回收一部分内存,内存空间为连续的，故可以直接隐式转换赋值
                    start_free = (char*)p;
                    end_free = start_free+i;

                    ///递归调用自己，为了修正nodjs
                    return chunk_alloc(bytes,nodjs);

                    ///@note: 任何残余零头终将被编入适当的free_list中备用

                }

            }
            end_free = 0;///如果出现意外(山穷水尽，到处没有内存用了)
            ///调用第一级配置器，看看out-of-memory机制能否尽力
            start_free = (char*)malloc(bytes_to_get);
            ///这会导致抛出异常(exception),或者内存不足的情况下得到改善

        }
        heap_size+=bytes_to_get;
        end_free=start_free+bytes_to_get;
        return chunk_alloc(bytes,nodjs);
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
    if(bytes>EMaxBytes::MAXBYTES){
        ///大于128bytes直接free
        free(ptr);
    } else{
        ///回收入内存池
        size_t index = FREELIST_INDEX(bytes);
        obj* node = static_cast<obj*>(ptr);
        node->next = free_list[index];
        free_list[index]=node;
    }
}

void *MySTL::Alloc::reallocate(void *ptr, size_t old_sz, size_t new_sz) {
    deallocate(ptr,old_sz);
    ptr = allocate(new_sz);
    return ptr;
}
