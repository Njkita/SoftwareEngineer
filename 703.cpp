#include <iostream>
#include <optional>
#include <string>

class Person {
 public:
  Person(const std::string &name) : name(name) {}

  void SetAge(int age_) { age = age_; }

  void ClearAge() { age.reset(); }

  void SetPhoneNumber(const std::string &phone_) { phonenumber = phone_; }

  void ClearPhoneNumber() { phonenumber.reset(); }

  void printInfo() const {
    std::cout << "Name: " << name << std::endl;
    if (age) {
      std::cout << "Age: " << *age << std::endl;
    } else {
      std::cout << "Age not specified" << std::endl;
    }
    if (phonenumber) {
      std::cout << "Phone number: " << *phonenumber << std::endl;
    } else {
      std::cout << "Phone number not specified" << std::endl;
    }
  }

 private:
  std::string name;
  std::optional<int> age;
  std::optional<std::string> phonenumber;
};

int main() {
  Person person("David Bowie");

  person.SetAge(69);
  person.SetPhoneNumber("+44-27-6492-5216");
  person.printInfo();
  person.ClearPhoneNumber();
  person.ClearAge();
  person.printInfo();

  return 0;
}
