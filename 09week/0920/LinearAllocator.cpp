#include "LinearAllocator.hpp"

LinearAllocator::LinearAllocator(std::size_t size) : m_size(size), m_offset(0)
{
    m_begin = operator new(m_size, std::align_val_t(s_alignment));
}

LinearAllocator::~LinearAllocator()
{
    if (m_begin)
    {
        operator delete(m_begin, m_size, std::align_val_t(s_alignment));
    }
}

void* LinearAllocator::allocate(std::size_t size, std::size_t alignment) override
{
    void* begin = static_cast<std::byte*>(m_begin) + m_offset;

    auto free = m_size - m_offset;

    if (begin = std::align(alignment, size, begin, free); begin)
    {
        m_offset = m_size - free + size;
        return begin;
    }
    else
    {
        return nullptr;
    }
}

void LinearAllocator::test() const override
{
    std::cout << "LinearAllocator::test : m_size = " << m_size << ' ';
    std::cout << "m_begin = " << std::format("{:018}", m_begin) << ' ';
    std::cout << "m_offset = " << std::format("{:0>4}", m_offset) << '\n';
}