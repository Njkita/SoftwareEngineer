#include <cmath>
#include <iostream>

template <typename... Args> constexpr size_t Convolution(Args &&...args) {
  return (sizeof(args) + ...);
}

template <typename T> constexpr size_t Recursive(T &&arg) {
  return sizeof(arg);
}

template <typename T, typename... Args>
constexpr size_t Recursive(T &&arg, Args &&...rest) {
  return sizeof(arg) + Recursive(std::forward<Args>(rest)...);
}

int main() {
  long long a = std::pow(10, 10);
  double b = 3.1415;
  char c = 'c';
  std::string d = "string";

  size_t sizeWithFold = Convolution(a, b, c, d);
  std::cout << "Convolution: " << sizeWithFold << " bytes\n";

  size_t sizeWithoutFold = Recursive(a, b, c, d);
  std::cout << "Recursive: " << sizeWithoutFold << " bytes\n";

  return 0;
}