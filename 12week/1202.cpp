#include <chrono>
#include <iostream>
#include <string>
#include <vector>

size_t find_sso_buffer_size() {
  std::string s;
  size_t capacity = s.capacity();

  for (size_t len = 1;; ++len) {
    s.push_back('x');
    if (s.capacity() != capacity) {
      return len - 1;
    }
  }
}

void performance_test(size_t sso_size) {
  const size_t num_iterations = 1000000;

  auto test = [num_iterations](size_t str_size) {
    auto start = std::chrono::high_resolution_clock::now();

    for (size_t i = 0; i < num_iterations; ++i) {
      std::string s(str_size, 'x');
    }

    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start)
        .count();
  };

  auto time_n = test(sso_size);
  auto time_n1 = test(sso_size + 1);

  std::cout << "Size (N): " << sso_size << "\n";
  std::cout << "N (" << sso_size << "): " << time_n << " μs\n";
  std::cout << "N+1 (" << sso_size + 1 << "): " << time_n1 << " μs\n";
  std::cout << (time_n1 - time_n) << " μs ("
            << (time_n1 * 100.0 / time_n - 100) << "% slower)\n";
}

int main() {
  size_t sso_size = find_sso_buffer_size();
  performance_test(sso_size);
  return 0;
}
