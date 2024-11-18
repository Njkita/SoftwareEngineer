#include <iostream>

struct Entity {
  virtual ~Entity() = default;
  virtual void test() const = 0;
};

struct Client1 {
  void test() const { std::clog << "Client1::test\n"; }
};

struct Client2 {
  void test() const { std::clog << "Client2::test\n"; }
};

template <typename ClientType>
class Adapter : public Entity {
private:
  ClientType client;
public:
  void test() const override { client.test(); }
};

int main() {
  Entity *entity1 = new Adapter<Client1>();
  entity1->test();
  Entity *entity2 = new Adapter<Client2>();
  entity2->test();
  delete entity1;
  return 0;
}
