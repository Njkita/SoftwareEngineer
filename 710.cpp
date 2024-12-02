#define BOOST_TEST_MODULE FindTest
#include <boost/test/included/unit_test.hpp>

#include <algorithm>
#include <cstddef>
#include <numeric>

template <class T> constexpr T midpoint(T a, T b) noexcept {
  return a + (b - a) / 2;
};
template <class T> constexpr T *midpoint(T *a, T *b) {
  return a + (b - a) / 2;
};

auto find(const int *array, std::size_t size, int key) {
  auto result = false;

  if (size > 0) {
    auto l = 0uz, r = size - 1, m = 0uz;

    while (l < r) {
      array[m = midpoint(l, r)] < key ? l = m + 1 : r = m;
    }

    result = array[l] == key;
  }

  return result;
}

BOOST_AUTO_TEST_CASE(TestFind) {
  int array[]{1, 2, 3, 4, 5};

  BOOST_TEST(find(array, std::size(array), 1));
  BOOST_TEST(find(array, std::size(array), 5));
  BOOST_TEST(find(array, std::size(array), 11));

  BOOST_TEST(!find(array, std::size(array), 0));
  BOOST_TEST(!find(array, std::size(array), 6));
  BOOST_TEST(!find(array, std::size(array), 3));

  BOOST_TEST(!find(nullptr, 0, 1));
}