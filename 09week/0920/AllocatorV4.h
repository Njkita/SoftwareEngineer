#ifndef ALLOCATOR_V4_H
#define ALLOCATOR_V4_H

#include "IAllocator.h"
#include <boost/noncopyable.hpp>

class AllocatorV4 : public IAllocator, private boost::noncopyable
{
public:
    AllocatorV4(std::size_t size);
    ~AllocatorV4() override;

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

    std::size_t m_size;
    void* m_begin;
    Node* m_head;
    static inline auto s_alignment = alignof(std::max_align_t);

    std::byte* get_byte(void* ptr) const;
    Node* get_node(void* ptr) const;
    Header* get_header(void* ptr) const;
    std::pair<Node*, Node*> find(std::size_t size) const;
    void merge(Node* previous, Node* node) const;
};

#endif