#ifndef SEGREGATED_LIST_ALLOCATOR_H
#define SEGREGATED_LIST_ALLOCATOR_H

#include "IAllocator.hpp"
#include <boost/noncopyable.hpp>

class SegregatedListAllocator : public IAllocator, private boost::noncopyable
{
public:
    SegregatedListAllocator(std::size_t size);
    ~SegregatedListAllocator() override;

    void* allocate(std::size_t size, std::size_t alignment = alignof(std::max_align_t)) override;
    void deallocate(void* ptr) override;
    void test() const override;

private:
    struct Node
    {
        std::size_t size;
        Node* next = nullptr;
    };

    struct Header
    {
        std::size_t size;
    };

    Node* m_head;

    std::byte* get_byte(void* ptr) const;
    Node* get_node(void* ptr) const;
    Header* get_header(void* ptr) const;
    std::pair<Node*, Node*> find(std::size_t size) const;
    void merge(Node* previous, Node* node) const;
};

#endif