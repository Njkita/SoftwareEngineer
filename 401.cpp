#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

//Реализуйте алгоритм сортировки кучей контейнера std::vector целочисленных значений через индексы.

template <typename T> void Sift_down(std::vector<T>& v, const int i, const int n) {
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

template <typename T> void HeapSort(std::vector<T>& v) {
    const int n = std::size(v);
    for (int i = n/2; i > 0; --i) {
        Sift_down(v, i-1, n);
    }
    int Size = n;
    while (Size > 1) {
        std::swap(v[0], v[Size - 1]);
        Size--;
        Sift_down(v, 0, Size);  
    }
}

template <typename T> void Cout(std::vector<T>& v) {
    std::copy(std::begin(v), std::end(v),
        std::ostream_iterator<T>(std::cout, " "));
    std::cout << std::endl;
    HeapSort(v);
    std::copy(std::begin(v), std::end(v),
        std::ostream_iterator<T>(std::cout, " "));
    std::cout << std::endl;
}

int main() {
    std::vector<int> intV = {0, 2, 167, 13, 13, 57, 723, 0, 34, 12, 167, 1};
    std::vector<double> doubleV = {5.7, 6.77, 3.584, 0.5, 6.771, 16.4};
    
    Cout(intV);
    Cout(doubleV);
}

    
