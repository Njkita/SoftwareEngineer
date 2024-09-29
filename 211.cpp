#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

//Реализуйте алгоритм сортировки кучей контейнера std::vector целочисленных значений через индексы.

void Sift_down(std::vector<int>& v, int i, int n) {
    if (2*i+1 < n) {    
        if (2*i+2 < n && v[i] < v[2*i + 2] && v[2*i + 1] < v[2*i + 2]) {
            std::swap(v[i], v[2*i + 2]);
            Sift_down(v, 2*i+2, n);
        }
        else if (v[i] < v[2*i + 1]) {
            std::swap(v[i], v[2*i + 1]);
            Sift_down(v, 2*i+1, n);
        }   
    }
}

void HeapSort(std::vector<int>& v) {
    int n = std::size(v);
    for (int i = n/2; i > 0; --i) {
        Sift_down(v, i-1, n);
    }
    int Size = n;
    while (Size > 1) {
        std::swap(v[0], v[Size - 1]);
        Size -= 1;
        Sift_down(v, 0, Size);  
    }
}


int main() {
    std::vector<int> v = {0, 2, 167, 13, 13, 57, 723, 0, 34, 12, 167, 1};

    std::copy(std::begin(v), std::end(v),
    std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    
    HeapSort(v);
    std::copy(std::begin(v), std::end(v),
    std::ostream_iterator<int>(std::cout, " "));
}

    
