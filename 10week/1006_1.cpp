#include <iostream>
#include <map>

struct NodeBase {
  void *parent;
  void *left;
  void *right;
};

template <typename Key, typename Value> struct Node : NodeBase {
  std::pair<const Key, Value> data;
};

// Получаем доступ к данным, которые хранит контейнер, как к полям класса
int main() {
  std::map<int, std::string> myMap = {{1, "One"}, {2, "Two"}, {3, "Three"}};

  auto it = myMap.find(2);
  // Получаем указатель на const ключ
  if (it != myMap.end()) {
    Node<int, std::string> *node = reinterpret_cast<Node<int, std::string> *>(
        const_cast<void *>(reinterpret_cast<const void *>(&(*it))));
    int *keyPtr = const_cast<int *>(&node->data.first);
    *keyPtr = 10;
  }

  std::cout << "Modified map:\n";
  for (const auto &[key, value] : myMap) {
    std::cout << key << " -> " << value << '\n';
  }

  return 0;
}
