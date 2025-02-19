#ifndef ALLOCATOR_V3_H
#define ALLOCATOR_V3_H

#include "IAllocator.h"
#include <boost/noncopyable.hpp>
#include <vector>

class AllocatorV3 : public IAllocator, private boost::noncopyable
{
public:
    AllocatorV3(std::size_t size, std::size_t step);
    ~AllocatorV3() override;

    void* allocate(std::size_t size, std::size_t alignment = alignof(std::max_align_t)) override;
    void deallocate(void* ptr) override;
    void test() const override;

private:
    struct Node
    {
        Node* next = nullptr;
    };

    std::size_t m_size, m_step, m_offset;
    void* m_begin;
    Node* m_head;
    std::vector<void*> m_lists;
    static inline auto s_alignment = alignof(std::max_align_t);

    std::byte* get_byte(void* ptr) const;
    Node* get_node(void* ptr) const;
    void make_list();
    Node* allocate_nodes() const;
};

#endif