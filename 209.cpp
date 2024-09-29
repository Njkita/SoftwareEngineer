#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

//Реализуйте алгоритм сортировки выбором контейнера std::vector целочисленных значений через индексы

void SelectionSort(std::vector<int>& v) {
    int n = std::size(v);
    for (int i = 0; i < n - 1; ++i) {
        int min_ = i; 
        for (int j = i + 1; j < n; ++j) {
            if (v[j] < v[min_]) {
                min_ = j;
            }
        }
        std::swap(v[i], v[min_]);
    }
}

int main() {
    std::vector<int> v = {0, 2, 167, 13, 13, 57, 723, 0, 34, 12, 167, 1};

    std::copy(std::begin(v), std::end(v),
    std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    SelectionSort(v);
    std::copy(std::begin(v), std::end(v),
    std::ostream_iterator<int>(std::cout, " "));
}

    
