cmake_minimum_required(VERSION 3.7)
project(MySTL)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp TypeTraits.hpp Iterator.hpp Allocator.hpp Alloc.cpp Alloc.h)
add_executable(MySTL ${SOURCE_FILES})