#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> tokenize(const std::string &str,
                                  const std::string &delimiters) {
  std::vector<std::string> tokens;
  size_t token_start = str.find_first_not_of(delimiters, 0);
  size_t token_end = str.find_first_of(delimiters, token_start);

  while (token_start != std::string::npos || token_end != std::string::npos) {
    tokens.push_back(str.substr(token_start, token_end - token_start));
    token_start = str.find_first_not_of(delimiters, token_end);
    token_end = str.find_first_of(delimiters, token_start);
  }

  return tokens;
}

int main() {
  std::string text = "Пример.разбиения/строки,на-лексемы";
  std::string delims = " ,./-";

  auto result = tokenize(text, delims);

  for (const auto &token : result) {
    std::cout << token << "\n";
  }

  return 0;
}