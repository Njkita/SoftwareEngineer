#include <iostream>
#include <memory>

namespace DataNamespace {
struct Data {
  int a;
  double b;
  std::string text;

  ~Data() { std::cout << "[~Data]\n"; }
};
}

namespace ContainerNamespace {
using namespace DataNamespace;

struct Container {
  std::shared_ptr<Data> data;

  explicit Container(int x, double y, std::string z)
      : data(std::make_shared<Data>(Data{x, y, std::move(z)})) {}

  std::shared_ptr<int> getA() { return {data, &data->a}; }
  std::shared_ptr<double> getB() { return {data, &data->b}; }
  std::shared_ptr<std::string> getText() { return {data, &data->text}; }
};
}

int main() {
  using namespace ContainerNamespace;

  std::cout << "Создаём контейнер\n";
  auto c = std::make_unique<Container>(42, 3.14, "Пример");

  {
    std::cout << "Получаем указатели\n";
    auto pA = c->getA();
    auto pB = c->getB();
    auto pText = c->getText();

    std::cout << "a: " << *pA << "\n";
    std::cout << "b: " << *pB << "\n";
    std::cout << "text: " << *pText << "\n";
    std::cout << "Выходим из области видимости\n";
  }

  {
    std::cout << "Новый shared_ptr на объект\n";
    auto pNew = c->data;
  }

  std::cout << "Уничтожаем контейнер\n";
  c.reset();
  std::cout << "Конец\n";
  return 0;
}
