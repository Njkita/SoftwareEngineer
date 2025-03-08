#ifndef FREE_LIST_ALLOCATOR_H
#define FREE_LIST_ALLOCATOR_H

#include "IAllocator.hpp"
#include <boost/noncopyable.hpp>
#include <vector>

class FreeListAllocator : public IAllocator, private boost::noncopyable
{
public:
    FreeListAllocator(std::size_t size, std::size_t step);
    ~FreeListAllocator() override;

    void* allocate(std::size_t size, std::size_t alignment = alignof(std::max_align_t)) override;
    void deallocate(void* ptr) override;
    void test() const override;

private:
    struct Node
    {
        Node* next = nullptr;
    };

    std::size_t m_step;
    Node* m_head;
    std::vector<void*> m_lists;

    std::byte* get_byte(void* ptr) const;
    Node* get_node(void* ptr) const;
    void make_list();
    Node* allocate_nodes() const;
};

#endif