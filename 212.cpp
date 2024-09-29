#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <bits/stdc++.h>

//Реализуйте алгоритм быстрой сортировки контейнера std::vector целочисленных значений через индексы

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

int MedianaMedian(std::vector<int>& v, int start, int end) {
    if (end - start <= 5) {
        std::vector<int> buf(v.begin() + start, v.begin() + end);
        InsertionSort(buf);
        return buf[std::size(buf) / 2];
    }
    
    std::vector<int> buf_v1;
    for (int i = start; i<end; i+=5) {
        int end_ind = std::min(i+5, end);
        std::vector<int> buf_v2(v.begin() + i, v.begin() + end_ind);
        InsertionSort(buf_v2);
        buf_v1.push_back(buf_v2[std::size(buf_v2)/2]);    
    }
    //InsertionSort(buf_v1);
    return MedianaMedian(buf_v1, 0, std::size(buf_v1));
}

int PartitionMM(std::vector<int>& v, int start, int end, int pivot) {
    int i = start;
    int j = end-1;
    while (i <= j) {
        while (i <= j && v[i] < pivot) {
            i+=1;
        }
        while (i <= j && v[j] > pivot) {
            j-=1;
        }
        if (i <= j) {
            std::swap(v[i], v[j]);
            i += 1;
            j -= 1;
        }
    }
    return i; 
}

int Partition2(std::vector<int>& v, int start, int end) {
    int pivot = v[end];
    int i = start;
    int j = end-1;
    while (i <= j) {
        while (i <= j && v[i] < pivot) {
            i += 1;
        }
        while (i <= j && v[j] > pivot) {
            j -= 1;
        }
        if (i <= j) {
            std::swap(v[i], v[j]);
            i += 1;
            j -= 1;
        }
    }
    std::swap(v[i], v[end]);
    return i; 
}

void QuickSortMM(std::vector<int>& v, int start, int end) {
    if (start >= end) return;
    int pivot = MedianaMedian(v, start, end);
    int pivot_index = PartitionMM(v, start, end, pivot);
    QuickSortMM(v, start, pivot_index - 1);
    QuickSortMM(v, pivot_index, end); 
}

void QuickSort2(std::vector<int>& v, int start, int end) {
    if (start < end) {
        int pivot_index = Partition2(v, start, end);
        QuickSort2(v, start, pivot_index - 1);
        QuickSort2(v, pivot_index + 1, end);
    }
}


int main() {
    std::vector<int> v = {0, 2, 167, 13, 13, 57, 723, 0, 34, 12, 167, 1, 18, 34, 5, 67, 11, 23, 17, 45, 8};

    std::copy(std::begin(v), std::end(v),
    std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    
    QuickSort2(v, 0, std::size(v)-1);
    std::copy(std::begin(v), std::end(v),
    std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    std::cout << "сортировка медианой медиан:" << std::endl;
    QuickSortMM(v, 0, std::size(v)-1);
    std::copy(std::begin(v), std::end(v),
    std::ostream_iterator<int>(std::cout, " "));
    
}

    
