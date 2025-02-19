#ifndef IALLOCATOR_H
#define IALLOCATOR_H

#include <cstddef>

class IAllocator
{
public:
    virtual ~IAllocator() = default;

    virtual void* allocate(std::size_t size, std::size_t alignment = alignof(std::max_align_t)) = 0;
    virtual void deallocate(void* ptr) = 0;
    virtual void test() const = 0;
};

#endif