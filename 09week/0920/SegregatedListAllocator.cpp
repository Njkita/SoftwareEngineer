#include "SegregatedListAllocator.hpp"

SegregatedListAllocator::SegregatedListAllocator(std::size_t size) : m_size(size), m_head(nullptr)
{
    if (m_size >= sizeof(Node) + 1)
    {
        m_begin = operator new(m_size, std::align_val_t(s_alignment));
        m_head = get_node(m_begin);
        m_head->size = m_size - sizeof(Header);
        m_head->next = nullptr;
    }
    else
    {
        throw std::runtime_error("invalid size");
    }
}

SegregatedListAllocator::~SegregatedListAllocator()
{
    if (m_begin)
    {
        operator delete(m_begin, m_size, std::align_val_t(s_alignment));
    }
}

void* SegregatedListAllocator::allocate(std::size_t size, std::size_t alignment) override
{
    void* end = get_byte(m_begin) + sizeof(Header) + size, * next = end;

    auto free = 2 * alignof(Header);

    if (next = std::align(alignof(Header), sizeof(Header), next, free); next)
    {
        auto padding = get_byte(next) - get_byte(end);

        if (auto [current, previous] = find(size + padding); current)
        {
            if (current->size >= size + padding + sizeof(Node) + 1)
            {
                auto step = sizeof(Header) + size + padding;
                auto node = get_node(get_byte(current) + step);
                node->size = current->size - step;
                node->next = current->next;
                current->next = node;
            }
            else
            {
                padding += current->size - size - padding;
            }

            if (!previous)
            {
                m_head = current->next;
            }
            else
            {
                previous->next = current->next;
            }

            auto header = get_header(current);
            header->size = size + padding;
            return get_byte(current) + sizeof(Header);
        }
    }

    return nullptr;
}

void SegregatedListAllocator::deallocate(void* ptr) override
{
    auto node = get_node(get_byte(ptr) - sizeof(Header));

    Node* previous = nullptr, * current = m_head;

    while (current)
    {
        if (node < current)
        {
            node->next = current;
            if (!previous)
            {
                m_head = node;
            }
            else
            {
                previous->next = node;
            }
            break;
        }

        previous = current;
        current = current->next;
    }

    merge(previous, node);
}

void SegregatedListAllocator::test() const override
{
    std::cout << "SegregatedListAllocator::test : ";
    std::cout << "m_size = " << m_size << ' ';
    std::cout << "m_begin = " << std::format("{:018}", m_begin) << ' ';
    std::cout << "m_head = " << std::format("{:018}", static_cast<void*>(m_head)) << ' ';

    if (m_head->next)
    {
        std::cout << "m_head->next = " << std::format("{:018}", static_cast<void*>(m_head->next));
    }

    std::cout << '\n';
}

std::byte* SegregatedListAllocator::get_byte(void* ptr) const
{
    return static_cast<std::byte*>(ptr);
}

SegregatedListAllocator::Node* SegregatedListAllocator::get_node(void* ptr) const
{
    return static_cast<Node*>(ptr);
}

SegregatedListAllocator::Header* SegregatedListAllocator::get_header(void* ptr) const
{
    return static_cast<Header*>(ptr);
}

std::pair<SegregatedListAllocator::Node*, SegregatedListAllocator::Node*> SegregatedListAllocator::find(std::size_t size) const
{
    Node* current = m_head, * previous = nullptr;

    while (current && size > current->size)
    {
        previous = current;
        current = current->next;
    }

    return std::make_pair(current, previous);
}

void SegregatedListAllocator::merge(Node* previous, Node* node) const
{
    if (node->next && get_byte(node) + sizeof(Header) + node->size == get_byte(node->next))
    {
        node->size += sizeof(Header) + node->next->size;
        node->next = node->next->next;
    }

    if (previous && get_byte(previous) + sizeof(Header) + previous->size == get_byte(node))
    {
        previous->size += sizeof(Header) + node->size;
        previous->next = node->next;
    }
}