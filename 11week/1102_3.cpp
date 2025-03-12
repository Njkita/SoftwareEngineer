#include <algorithm>
#include <cassert>
#include <cstddef>
#include <functional>
#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

// Используем лямбда-выражение

template <typename Compare>
void sort(std::vector<int> &vector, std::size_t left, std::size_t right,
          Compare comp) {
  for (auto i = left + 1; i < right; ++i) {
    for (auto j = i; j > left; --j) {
      if (comp(vector[j], vector[j - 1])) {
        std::swap(vector[j], vector[j - 1]);
      }
    }
  }
}

template <typename Compare>
void merge(std::vector<int> &vector, std::size_t left, std::size_t middle,
           std::size_t right, Compare comp) {
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

template <typename Compare>
void split(std::vector<int> &vector, std::size_t left, std::size_t right,
           Compare comp) {
  if (right - left <= 64) {
    sort(vector, left, right, comp);
  } else {
    auto middle = std::midpoint(left, right);

    split(vector, left, middle, comp);
    split(vector, middle, right, comp);
    merge(vector, left, middle, right, comp);
  }
}

template <typename Compare>
void timsort(std::vector<int> &vector, Compare comp) {
  split(vector, 0, std::size(vector), comp);
}

int main() {
  auto size = 1'000uz;
  std::vector<int> vector(size, 0);

  for (auto i = 0uz; i < size; ++i) {
    vector[i] = size - i;
  }

  timsort(vector, [](int a, int b) { return a < b; });
  assert(std::ranges::is_sorted(vector));

  timsort(vector, [](int a, int b) { return a > b; });
  assert(std::ranges::is_sorted(vector, std::greater{}));

  std::cout << "Sorting with lambda expressions: OK\n";
}