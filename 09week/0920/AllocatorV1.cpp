#include "AllocatorV1.h"
#include <new>
#include <iostream>
#include <format>

AllocatorV1::AllocatorV1(std::size_t size) : m_size(size), m_offset(0)
{
    m_begin = operator new(m_size, std::align_val_t(s_alignment));
}

AllocatorV1::~AllocatorV1()
{
    if (m_begin)
    {
        operator delete(m_begin, m_size, std::align_val_t(s_alignment));
    }
}

void* AllocatorV1::allocate(std::size_t size, std::size_t alignment)
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

void AllocatorV1::test() const
{
    std::cout << "AllocatorV1::test : m_size = " << m_size << ' ';
    std::cout << "m_begin = " << std::format("{:018}", m_begin) << ' ';
    std::cout << "m_offset = " << std::format("{:0>4}", m_offset) << '\n';
}