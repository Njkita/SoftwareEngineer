#include <iostream>
#include <string>

class Person_ {
public:
  std::string name;
  int age = 0;
  int height = 0;

  void entering() const {
    std::cout << "Name: " << name << ", Age: " << age << ", Height: " << height
              << std::endl;
  }
};

class Builder {
public:
  Builder &name(const std::string &name) {
    person.name = name;
    return *this;
  }

  Builder &age(int age) {
    person.age = age;
    return *this;
  }

  Builder &height(int height) {
    person.height = height;
    return *this;
  }

  Person_ get() const { return person; }

private:
  Person_ person;
};

int main() {
  Builder builder;
  Person_ p = builder.name("Ivan").age(26).height(180).get();

  p.entering();

  return 0;
}