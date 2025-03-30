#include <cctype>
#include <iostream>
#include <string>


std::string capitalizeWords(std::string text) {
  auto it = text.begin();
  bool newWord = true;

  while (it != text.end()) {
    if (isalpha(*it)) {
      *it = newWord ? toupper(*it) : tolower(*it);
      newWord = false;
    } else {
      newWord = true;
    }
    ++it;
  }

  return text;
}

int main() {
  std::string test = "heLLo, woRLD!";
  std::cout << capitalizeWords(test) << std::endl;
  return 0;
}