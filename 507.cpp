#include <iostream>


struct Client {
  void test() const { std::clog << "Client::test\n"; }
};

struct Entity {
  virtual ~Entity() = default;
  virtual void test() const = 0;
};

class Adapter : private Client, public Entity {
public:
  void test() const override { Client::test(); }
};

int main() {
  Entity *entity = new Adapter();
  entity->test();

  delete entity;
}