#include <algorithm>
#include <iostream>
#include <vector>


template <typename InputIt, typename OutputIt, typename UnaryOp,
          typename Predicate>
OutputIt transform_if(InputIt first, InputIt last, OutputIt d_first,
                      UnaryOp unary_op, Predicate pred) {
  for (; first != last; ++first) {
    if (pred(*first)) {
      *d_first++ = unary_op(*first);
    }
  }
  return d_first;
}

int main() {
  std::vector<int> input = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<int> output;

  auto pred = [](int x) { return x % 2 == 0; };
  auto op = [](int x) { return x * x; };

  output.reserve(input.size());

  transform_if(input.begin(), input.end(), std::back_inserter(output), op,
               pred);

  for (int n : output) {
    std::cout << n << " ";
  }
  std::cout << std::endl;

  return 0;
}
