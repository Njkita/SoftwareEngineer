#include <iostream>
#include <ostream>
#include <stdexcept>

struct Entity {
  virtual ~Entity() = default;

  friend auto &operator<<(std::ostream &stream, const Entity &entity) {
    try {
      return entity.print(stream);
    } catch (const std::exception &e) {
      throw std::runtime_error("Error while printing Entity: " +
                               std::string(e.what()));
    }
  }

  virtual std::ostream &print(std::ostream &stream) const {
    if (!stream) {
      throw std::ios_base::failure("Invalid stream");
    }
    return stream << "Entity";
  }
};

struct Client : public Entity {
  std::ostream &print(std::ostream &stream) const override {
    if (!stream) {
      throw std::ios_base::failure("Invalid stream in Client");
    }
    return stream << "Client";
  }
};

int main() {
  try {
    Entity *entity = new Client();

    try {
      std::cout << "*entity = " << *entity << '\n';
    } catch (const std::exception &e) {
      std::cerr << "Error: " << e.what() << std::endl;
    }

    delete entity;
  } catch (const std::exception &e) {
    std::cerr << "Unexpected error: " << e.what() << std::endl;
  }

  return 0;
}
