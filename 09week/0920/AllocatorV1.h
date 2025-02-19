#ifndef ALLOCATOR_V1_H
#define ALLOCATOR_V1_H

#include "IAllocator.h"
#include <boost/noncopyable.hpp>

class AllocatorV1 : public IAllocator, private boost::noncopyable
{
public:
    AllocatorV1(std::size_t size);
    ~AllocatorV1() override;

    void* allocate(std::size_t size, std::size_t alignment = alignof(std::max_align_t)) override;
    void deallocate(void* ptr) override;
    void test() const override;

private:
    std::size_t m_size, m_offset;
    void* m_begin;
    static inline auto s_alignment = alignof(std::max_align_t);
};

#endif