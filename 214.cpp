#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <bits/stdc++.h>

//Реализуйте алгоритм обращения порядка элементов контейнера std::vector целочисленных значений

void Reverse(std::vector<size_t>& v) {
    size_t i = 0;
    size_t j = v.size() - 1;

    while (i < j) {
        std::swap(v[i], v[j]);
        i += 1;
        j -= 1;
    }
}


int main() {
    std::vector<size_t> v = {0, 2, 167, 13, 13, 57, 723, 0, 34, 12, 167, 1, 18, 34, 5, 67, 11, 23, 17, 45, 8};

    std::copy(std::begin(v), std::end(v),
    std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    
    Reverse(v);
    std::copy(std::begin(v), std::end(v),
    std::ostream_iterator<int>(std::cout, " "));
}

    
