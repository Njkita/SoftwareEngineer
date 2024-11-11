#include <iostream>
#include <string>

struct Entity {
  virtual ~Entity() = default;

  virtual void test() const = 0;
};

struct Client : public Entity {
  void test() const override { std::clog << "Client::test\n"; }
};
struct Server : public Entity {
  void test() const override { std::clog << "Server::test\n"; }
};

template <typename T> class Decorator : public T {
public:
  template <typename... Args>
  explicit Decorator(Args &&...args) : T(std::forward<Args>(args)...) {}

  void test() const override {
    std::clog << "Decorator::";
    T::test();
  }
};

int main() {
  Client client;
  Decorator<Client> decorated_client(client);

  client.test();
  decorated_client.test();

  return 0;
}