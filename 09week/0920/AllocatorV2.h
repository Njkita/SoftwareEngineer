#ifndef ALLOCATOR_V2_H
#define ALLOCATOR_V2_H

#include "IAllocator.h"
#include <boost/noncopyable.hpp>

class AllocatorV2 : public IAllocator, private boost::noncopyable
{
public:
    AllocatorV2(std::size_t size);
    ~AllocatorV2() override;

    void* allocate(std::size_t size, std::size_t alignment = alignof(std::max_align_t)) override;
    void deallocate(void* ptr) override;
    void test() const override;

private:
    struct Header
    {
        std::size_t size;
    };

    std::size_t m_size, m_offset;
    void* m_begin;
    static inline auto s_alignment = alignof(std::max_align_t);

    std::byte* get_byte(void* ptr) const;
    Header* get_header(void* ptr) const;
};

#endif