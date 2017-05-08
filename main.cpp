#include <iostream>
#include "Allocator.hpp"
#include <new>
#include <cstdio>
#include <cstdlib>

using namespace MySTL;

///@todo test alloc
///@todo finish vector
///@todo finish readme

int a[5] = {1,2,3,4,5};

///@brief 测试Operator New
void testOperatorNew(){
    Allocator<int> allocator;

    int* p = allocator.allocate(10);

    std::cout<< sizeof(p)<<std::endl;

    ///@brief ::operator new 为全局名字空间中new操作符
    void* tmp = ::operator new(1000);
    void* mtmp = malloc(40);
    std::cout<< sizeof(tmp)<<std::endl;
    std::cout<< sizeof(mtmp)<<std::endl;

    allocator.deallocate(static_cast<int*>(tmp));

}

///@brief 测试其它零散事务
void testOther(){
    union node{
        node* next;
        char c[1];
    };
    std::cout<< sizeof(char)<<" "<< sizeof(node)<<std::endl;

    for(int i = 0;i<5;i++){
        std::cout<<a[i]<<std::endl;
    }
}
int main() {
//    std::cout << "Hello, World!" << std::endl;

//    testOperatorNew();

//    testOther();
    return 0;
}