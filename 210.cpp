#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

//Реализуйте алгоритм сортировки Шелла контейнера std::vector целочисленных значений через индексы

void InsertionSort(std::vector<int>& v) {
    int n = std::size(v);
    for (int i = 1; i < n ; ++i) { 
        int j = i;
        while ((j > 0) && (v[j] < v[j-1])) {
            std::swap(v[j], v[j-1]);
            j-=1;
        }
    }
}

void ShellSort(std::vector<int>& v) {
    int n = std::size(v);
    int h = n/2;
    while (h > 0) {
        for (int j = 0; j < h ; ++j) {
            std::vector<int> v_buf;
            for (int i = j; i < n; i+=h) { 
                    v_buf.push_back(v[i]);
            }
            InsertionSort(v_buf);
            for (int i = j, k = 0; i < n; i += h, ++k) { 
                    v[i] = v_buf[k];
            }
        }
        h = h/2;
    }
}


int main() {
    std::vector<int> v = {0, 2, 167, 13, 13, 57, 723, 0, 34, 12, 167, 1};

    std::copy(std::begin(v), std::end(v),
    std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    
    ShellSort(v);
    std::copy(std::begin(v), std::end(v),
    std::ostream_iterator<int>(std::cout, " "));
}

    
