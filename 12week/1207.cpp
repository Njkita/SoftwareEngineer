#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::string join_strings(const std::vector<std::string> &strings,
                         const std::string &delimiter) {
  if (strings.empty()) {
    return "";
  }

  std::ostringstream oss;
  oss << strings[0];

  for (size_t i = 1; i < strings.size(); ++i) {
    oss << delimiter << strings[i];
  }

  return oss.str();
}

int main() {
  std::vector<std::string> words = {"world1", "world2", "world3"};

  std::string delimiter;
  std::cout << "Разделитель: ";
  std::getline(std::cin, delimiter);

  std::string result = join_strings(words, delimiter);
  std::cout << result << std::endl;

  return 0;
}