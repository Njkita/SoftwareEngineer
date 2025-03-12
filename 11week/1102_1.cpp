#include <algorithm>
#include <cassert>
#include <cstddef>
#include <functional>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

// Используем указатель на функцию

using CompareFunction = bool (*)(int, int);
void sort(std::vector<int> &vector, std::size_t left, std::size_t right,
          CompareFunction comp) {
  for (auto i = left + 1; i < right; ++i) {
    for (auto j = i; j > left; --j) {
      if (comp(vector[j], vector[j - 1])) {
        std::swap(vector[j], vector[j - 1]);
      }
    }
  }
}

void merge(std::vector<int> &vector, std::size_t left, std::size_t middle,
           std::size_t right, CompareFunction comp) {
  std::vector<int> buffer(right - left, 0);

  for (auto i = left, j = middle, k = 0uz; k < std::size(buffer); ++k) {
    if (i < middle &&
        ((j < right && comp(vector[i], vector[j])) || j == right)) {
      buffer[k] = vector[i++];
    } else {
      buffer[k] = vector[j++];
    }
  }

  for (auto i = 0uz, j = 0uz; j < std::size(buffer); ++j) {
    vector[left + i++] = buffer[j];
  }
}

void split(std::vector<int> &vector, std::size_t left, std::size_t right,
           CompareFunction comp) {
  if (right - left <= 64) {
    sort(vector, left, right, comp);
  } else {
    auto middle = std::midpoint(left, right);

    split(vector, left, middle, comp);
    split(vector, middle, right, comp);
    merge(vector, left, middle, right, comp);
  }
}

void timsort(std::vector<int> &vector, CompareFunction comp) {
  split(vector, 0, std::size(vector), comp);
}

bool ascending(int a, int b) { return a < b; }
bool descending(int a, int b) { return a > b; }

int main() {
  auto size = 1'000uz;
  std::vector<int> vector(size, 0);

  for (auto i = 0uz; i < size; ++i) {
    vector[i] = size - i;
  }

  timsort(vector, ascending);
  assert(std::ranges::is_sorted(vector));

  timsort(vector, descending);
  assert(std::ranges::is_sorted(vector, std::greater{}));

  std::cout << "Sorting with function pointers: OK\n";
}