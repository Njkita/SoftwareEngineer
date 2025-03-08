#ifndef IALLOCATOR_H
#define IALLOCATOR_H

#include <cstddef>
#include <new>
#include <iostream>
#include <format>

class IAllocator
{
public:
    virtual ~IAllocator() = default;

    virtual void* allocate(std::size_t size, std::size_t alignment = alignof(std::max_align_t)) = 0;
    virtual void deallocate(void* ptr) = 0;
    virtual void test() const = 0;

protected:
    std::size_t m_size, m_offset;
    void* m_begin;
    static inline auto s_alignment = alignof(std::max_align_t);
};

#endif