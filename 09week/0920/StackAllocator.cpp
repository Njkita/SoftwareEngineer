#include "StackAllocator.hpp"

StackAllocator::StackAllocator(std::size_t size) : m_size(size), m_offset(0)
{
    m_begin = operator new(m_size, std::align_val_t(s_alignment));
}

StackAllocator::~StackAllocator()
{
    if (m_begin)
    {
        operator delete(m_begin, m_size, std::align_val_t(s_alignment));
    }
}

void* StackAllocator::allocate(std::size_t size, std::size_t alignment) override
{
    void* begin = get_byte(m_begin) + m_offset + sizeof(Header);

    auto free = m_size - m_offset - sizeof(Header);

    if (begin = std::align(alignment, size, begin, free); begin)
    {
        auto header = get_header(get_byte(begin) - sizeof(Header));
        *header = std::distance(get_byte(m_begin) + m_offset, get_byte(begin));
        m_offset = get_byte(begin) - get_byte(m_begin) + size;
        return begin;
    }
    else
    {
        return nullptr;
    }
}

void StackAllocator::deallocate(void* ptr) override
{
    auto header = get_header(get_byte(ptr) - sizeof(Header));
    m_offset = get_byte(ptr) - get_byte(m_begin) - *header;
}

void StackAllocator::test() const override
{
    std::cout << "StackAllocator::test : m_size = " << m_size << ' ';
    std::cout << "m_begin = " << std::format("{:018}", m_begin) << ' ';
    std::cout << "m_offset = " << std::format("{:0>4}", m_offset) << '\n';
}

std::byte* StackAllocator::get_byte(void* ptr) const
{
    return static_cast<std::byte*>(ptr);
}

StackAllocator::Header* StackAllocator::get_header(void* ptr) const
{
    return static_cast<Header*>(ptr);
}