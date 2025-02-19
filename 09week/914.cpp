#include <iostream>
#include <iterator>

class OddIter {
    int num;
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = int;
    using difference_type = std::ptrdiff_t;
    using pointer = int*;
    using reference = int&;

    explicit OddIter(int start) : num(start % 2 == 0 ? start + 1 : start) {}

    int operator*() const { return num; }
    OddIter& operator++() { num += 2; return *this; }
    OddIter operator++(int) { OddIter tmp = *this; ++(*this); return tmp; }
    bool operator==(const OddIter& other) const { return num == other.num; }
    bool operator!=(const OddIter& other) const { return !(*this == other); }
};

int main() {
    OddIter begin(1), end(117);
    for (auto it = begin; it != end; ++it) {
        std::cout << *it << " ";
    }
    return 0;
}
