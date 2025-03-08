cmake_minimum_required(VERSION 3.10)
project(Allocators)

set(CMAKE_CXX_STANDARD 20)

add_library(Allocators STATIC
    IAllocator.hpp
    LinearAllocator.hpp LinearAllocator.cpp
    StackAllocator.hpp StackAllocator.cpp
    FreeListAllocator.hpp FreeListAllocator.cpp
    SegregatedListAllocator.hpp SegregatedListAllocator.cpp
)

target_include_directories(Allocators INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
