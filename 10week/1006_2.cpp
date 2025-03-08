#include <iostream>
#include <map>

//нарушаем константность

int main() {
  std::map<int, std::string> myMap = {{1, "One"}, {2, "Two"}, {3, "Three"}};

  auto it = myMap.find(2);
  if (it != myMap.end()) {
    int *keyPtr = const_cast<int *>(&it->first);
    *keyPtr = 10;
  }

  std::cout << "Modified map:\n";
  for (const auto &[key, value] : myMap) {
    std::cout << key << " -> " << value << '\n';
  }

  return 0;
}
