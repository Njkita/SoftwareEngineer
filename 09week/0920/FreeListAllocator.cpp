#include "FreeListAllocator.hpp"

FreeListAllocator::FreeListAllocator(std::size_t size, std::size_t step)
    : m_size(size), m_step(step), m_offset(0), m_head(nullptr)
{
    if (m_size % m_step == 0 && m_step >= sizeof(Node))
    {
        make_list();
        m_begin = m_head;
    }
    else
    {
        throw std::runtime_error("invalid size");
    }
}

FreeListAllocator::~FreeListAllocator()
{
    for (auto list : m_lists)
    {
        if (list)
        {
            operator delete(list, m_size, std::align_val_t(s_alignment));
        }
    }
}

void* FreeListAllocator::allocate(std::size_t size, std::size_t alignment) override
{
    if (!m_head)
    {
        if (m_offset == std::size(m_lists))
        {
            make_list();
        }
        else
        {
            m_head = get_node(m_lists[++m_offset - 1]);
        }
    }

    auto node = m_head;

    if (!node->next)
    {
        auto next = get_byte(node) + m_step;

        if (next != get_byte(m_lists[m_offset - 1]) + m_size)
        {
            m_head = get_node(next);
            m_head->next = nullptr;
        }
        else
        {
            m_head = m_head->next;
        }
    }
    else
    {
        m_head = m_head->next;
    }

    return node;
}

void FreeListAllocator::deallocate(void* ptr) override
{
    auto node = get_node(ptr);
    node->next = m_head;
    m_head = node;
}

void FreeListAllocator::test() const override
{
    std::cout << "FreeListAllocator::test : ";
    std::cout << "m_size = " << m_size << ' ' << "m_step = " << m_step << ' ';
    std::cout << "m_begin = " << std::format("{:018}", m_begin) << ' ';
    std::cout << "m_head = " << std::format("{:018}", static_cast<void*>(m_head)) << ' ';
    std::cout << "m_offset = " << m_offset << '\n';
}

std::byte* FreeListAllocator::get_byte(void* ptr) const
{
    return static_cast<std::byte*>(ptr);
}

FreeListAllocator::Node* FreeListAllocator::get_node(void* ptr) const
{
    return static_cast<Node*>(ptr);
}

void FreeListAllocator::make_list()
{
    m_head = allocate_nodes();
    ++m_offset;
    m_lists.push_back(m_head);
}

FreeListAllocator::Node* FreeListAllocator::allocate_nodes() const
{
    auto node = get_node(operator new(m_size, std::align_val_t(s_alignment)));
    node->next = nullptr;
    return node;
}