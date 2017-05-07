#include <iostream>
#include "Allocator.hpp"
#include <new>
#include <cstdio>
#include <cstdlib>

using namespace MySTL;

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
int main() {
//    std::cout << "Hello, World!" << std::endl;

    testOperatorNew();

    return 0;
}