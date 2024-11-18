#include <iostream>
#include <memory>

struct Entity {
  virtual ~Entity() = default;

  virtual void test() const { std::clog << "Default Entity::test\n"; }
};

struct Client : public Entity {
  void test() const override { std::clog << "Client::test\n"; }
};

struct Server : public Entity {
  void test() const override { std::clog << "Server::test\n"; }
};

class Decorator : public Entity {
public:
  explicit Decorator(std::shared_ptr<Entity> entity)
      : m_entity(std::move(entity)) {}

  virtual void test() const override = 0;

protected:
  std::shared_ptr<Entity> m_entity;
};

void DefaultDecoratorTest(const Decorator &decorator) {
  std::clog << "Default Decorator::test\n";
}

struct Decorated_Entity : public Decorator {
  explicit Decorated_Entity(std::shared_ptr<Entity> entity)
      : Decorator(std::move(entity)) {}

  void test() const override {
    std::clog << "Decorated_Entity::";
    m_entity->test();
  }
};

int main() {
  auto client = std::make_shared<Client>();
  auto decorated = std::make_shared<Decorated_Entity>(client);

  client->test();
  decorated->test();

  return 0;
}
