cmake_minimum_required(VERSION 3.10)
project(Allocators)

set(CMAKE_CXX_STANDARD 20)

add_library(Allocators STATIC
    IAllocator.h
    AllocatorV1.h AllocatorV1.cpp
    AllocatorV2.h AllocatorV2.cpp
    AllocatorV3.h AllocatorV3.cpp
    AllocatorV4.h AllocatorV4.cpp
)

target_include_directories(Allocators PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})