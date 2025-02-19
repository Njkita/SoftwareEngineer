#include "AllocatorV2.h"
#include <new>
#include <iostream>
#include <format>

AllocatorV2::AllocatorV2(std::size_t size) : m_size(size), m_offset(0)
{
    m_begin = operator new(m_size, std::align_val_t(s_alignment));
}

AllocatorV2::~AllocatorV2()
{
    if (m_begin)
    {
        operator delete(m_begin, m_size, std::align_val_t(s_alignment));
    }
}

void* AllocatorV2::allocate(std::size_t size, std::size_t alignment)
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

void AllocatorV2::deallocate(void* ptr)
{
    auto header = get_header(get_byte(ptr) - sizeof(Header));
    m_offset = get_byte(ptr) - get_byte(m_begin) - *header;
}

void AllocatorV2::test() const
{
    std::cout << "AllocatorV2::test : m_size = " << m_size << ' ';
    std::cout << "m_begin = " << std::format("{:018}", m_begin) << ' ';
    std::cout << "m_offset = " << std::format("{:0>4}", m_offset) << '\n';
}

std::byte* AllocatorV2::get_byte(void* ptr) const
{
    return static_cast<std::byte*>(ptr);
}

AllocatorV2::Header* AllocatorV2::get_header(void* ptr) const
{
    return static_cast<Header*>(ptr);
}