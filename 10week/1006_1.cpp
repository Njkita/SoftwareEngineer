#include <iostream>
#include <map>

// Грубо меняем память через reinterpret_cast

int main() {
  std::map<int, std::string> myMap = {{1, "One"}, {2, "Two"}, {3, "Three"}};

  auto it = myMap.find(2);
  if (it != myMap.end()) {
    int *keyPtr = reinterpret_cast<int *>(
        const_cast<void *>(static_cast<const void *>(&it->first)));
    *keyPtr = 10;
  }

  std::cout << "Modified map:\n";
  for (const auto &[key, value] : myMap) {
    std::cout << key << " -> " << value << '\n';
  }

  return 0;
}
