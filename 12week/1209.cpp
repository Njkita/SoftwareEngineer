#include <iostream>
#include <string>

std::string compress_string(const std::string &input) {
  if (input.empty())
    return "";

  std::string compressed;
  char current = input[0];
  int count = 1;

  for (size_t i = 1; i < input.size(); ++i) {
    if (input[i] == current) {
      ++count;
    } else {
      compressed += current;
      if (count > 1) {
        compressed += std::to_string(count);
      }
      current = input[i];
      count = 1;
    }
  }

  compressed += current;
  if (count > 1) {
    compressed += std::to_string(count);
  }

  return compressed;
}

int main() {
  std::string test = "aaabbbcccd";
  std::cout << test << "\n";
  std::cout << compress_string(test) << "\n";
  return 0;
}