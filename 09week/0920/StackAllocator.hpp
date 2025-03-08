#ifndef STACK_ALLOCATOR_H
#define STACK_ALLOCATOR_H

#include "IAllocator.hpp"
#include <boost/noncopyable.hpp>

class StackAllocator : public IAllocator, private boost::noncopyable
{
public:
    StackAllocator(std::size_t size);
    ~StackAllocator() override;

    void* allocate(std::size_t size, std::size_t alignment = alignof(std::max_align_t)) override;
    void deallocate(void* ptr) override;
    void test() const override;

private:
    struct Header
    {
        std::size_t size;
    };

    std::byte* get_byte(void* ptr) const;
    Header* get_header(void* ptr) const;
};

#endif