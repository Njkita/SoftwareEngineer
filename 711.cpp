#define BOOST_TEST_MODULE TimSortTest
#include <boost/test/included/unit_test.hpp>

#include <algorithm>
#include <cassert>
#include <numeric>
#include <ranges>
#include <vector>


template <class T> constexpr T midpoint(T a, T b) noexcept {
  return a + (b - a) / 2;
};
template <class T> constexpr T *midpoint(T *a, T *b) {
  return a + (b - a) / 2;
};

void sort(std::vector<int> &vector, std::size_t left, std::size_t right) {
  for (auto i = left + 1; i < right; ++i) {
    for (auto j = i; j > left; --j) {
      if (vector[j - 1] < vector[j]) {
        std::swap(vector[j], vector[j - 1]);
      }
    }
  }
}

void merge(std::vector<int> &vector, std::size_t left, std::size_t middle,
           std::size_t right) {
  std::vector<int> copy(right - left, 0);

  for (auto i = left, j = middle; auto &element : copy) {
    if (i < middle && ((j < right && vector[i] >= vector[j]) || j == right)) {
      element = vector[i++];
    } else {
      element = vector[j++];
    }
  }

  for (auto i = 0uz; auto element : copy) {
    vector[left + i++] = element;
  }
}

void split(std::vector<int> &vector, std::size_t left, std::size_t right) {
  if (right - left <= 64) {
    sort(vector, left, right);
  } else {
    auto middle = midpoint(left, right);

    split(vector, left, middle);
    split(vector, middle, right);
    merge(vector, left, middle, right);
  }
}

void timsort(std::vector<int> &vector, std::size_t left, std::size_t right) {
  split(vector, left, right);
}

BOOST_AUTO_TEST_CASE(SortedAscending) {
  std::vector<int> vector{1, 2, 3, 4, 5};
  timsort(vector, 0, vector.size());
  BOOST_TEST(std::is_sorted(vector.begin(), vector.end(), [](int a, int b) {
        return a > b;
    }));
}

BOOST_AUTO_TEST_CASE(SortedDescending) {
  std::vector<int> vector{5, 4, 3, 2, 1};
  timsort(vector, 0, vector.size());
  BOOST_TEST(std::is_sorted(vector.begin(), vector.end(), [](int a, int b) {
        return a > b;
    }));
}

BOOST_AUTO_TEST_CASE(RandomOrder) {
  std::vector<int> vector{3, 1, 4, 1, 5, 9, 2, 6};
  timsort(vector, 0, vector.size());
  BOOST_TEST(std::is_sorted(vector.begin(), vector.end(), [](int a, int b) {
        return a > b;
    }));
}

BOOST_AUTO_TEST_CASE(Duplicates) {
  std::vector<int> vector{1, 1, 1, 1, 1, 1};
  timsort(vector, 0, vector.size());
  BOOST_TEST(std::is_sorted(vector.begin(), vector.end(), [](int a, int b) {
        return a > b;
    }));
}