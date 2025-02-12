#include <iostream>
#include <memory>

template <typename T> class Tree {
private:
  struct Node {
    T data;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    std::weak_ptr<Node> parent;

    explicit Node(T value) : data(value) {
      std::cout << "Создан узел: " << data << "\n";
    }

    ~Node() { std::cout << "Удалён узел: " << data << "\n"; }
  };

  std::shared_ptr<Node> root;

public:
  void insert(T value) {
    if (!root) {
      root = std::make_shared<Node>(value);
    } else {
      insertHelper(root, value);
    }
  }

  bool find(T value) const { return findHelper(root, value); }

  void print() const {
    printHelper(root);
    std::cout << "\n";
  }

private:
  void insertHelper(std::shared_ptr<Node> node, T value) {
    if (value < node->data) {
      if (node->left) {
        insertHelper(node->left, value);
      } else {
        node->left = std::make_shared<Node>(value);
        node->left->parent = node;
      }
    } else {
      if (node->right) {
        insertHelper(node->right, value);
      } else {
        node->right = std::make_shared<Node>(value);
        node->right->parent = node;
      }
    }
  }

  bool findHelper(std::shared_ptr<Node> node, T value) const {
    if (!node)
      return false;
    if (value == node->data)
      return true;
    return value < node->data ? findHelper(node->left, value)
                              : findHelper(node->right, value);
  }

  void printHelper(std::shared_ptr<Node> node) const {
    if (!node)
      return;
    printHelper(node->left);
    std::cout << node->data << " ";
    printHelper(node->right);
  }
};

int main() {
  {
    Tree<int> tree;
    tree.insert(8);
    tree.insert(20);
    tree.insert(3);
    tree.insert(14);
    tree.insert(88);
    tree.insert(20);
    tree.insert(33);

    std::cout << "Обход: ";
    tree.print();

    std::cout << "Поиск 7: " << (tree.find(88) ? "найдено" : "не найдено")
              << "\n";
  }

  std::cout << "Дерево удалено\n";
  return 0;
}
