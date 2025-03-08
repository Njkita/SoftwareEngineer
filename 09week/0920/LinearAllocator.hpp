#ifndef LINEAR_ALLOCATOR_H
#define LINEAR_ALLOCATOR_H

#include "IAllocator.hpp"
#include <boost/noncopyable.hpp>

class LinearAllocator : public IAllocator, private boost::noncopyable
{
public:
    LinearAllocator(std::size_t size);
    ~LinearAllocator() override;

    void* allocate(std::size_t size, std::size_t alignment = alignof(std::max_align_t)) override;
    void deallocate(void* ptr) override;
    void test() const override;
};

#endif