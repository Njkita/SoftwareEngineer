#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index_container.hpp>
#include <iostream>
#include <string>


struct Contact {
  std::string last_name;
  std::string first_name;
  std::string phone_number;

  Contact(std::string ln, std::string fn, std::string pn)
      : last_name(std::move(ln)), first_name(std::move(fn)),
        phone_number(std::move(pn)) {}

  void print() const {
    std::cout << last_name << " " << first_name << ": " << phone_number << '\n';
  }
};

struct by_last_name {};
struct by_insert_order {};
struct by_phone_number {};

using Phonebook = boost::multi_index::multi_index_container<
    Contact,
    boost::multi_index::indexed_by<
        boost::multi_index::ordered_non_unique<
            boost::multi_index::tag<by_last_name>,
            boost::multi_index::member<Contact, std::string,
                                       &Contact::last_name>>,
        boost::multi_index::sequenced<boost::multi_index::tag<by_insert_order>>,
        boost::multi_index::hashed_unique<
            boost::multi_index::tag<by_phone_number>,
            boost::multi_index::member<Contact, std::string,
                                       &Contact::phone_number>>>>;

int main() {
  Phonebook phonebook;

  phonebook.insert({"Ivanov", "Andrey", "+74952345608"});
  phonebook.insert({"Petrov", "Igor", "+790998765403"});
  phonebook.insert({"Ivanilov", "Egor", "+79175260880"});

  std::cout << "Справочник по фамилии:\n";
  for (const auto &contact : phonebook.get<by_last_name>()) {
    contact.print();
  }

  std::cout << "\nСправочник по порядку вставки:\n";
  for (const auto &contact : phonebook.get<by_insert_order>()) {
    contact.print();
  }

  auto &phone_index = phonebook.get<by_phone_number>();
  auto it = phone_index.find("+790998765403");
  if (it != phone_index.end()) {
    std::cout << "\nНайден контакт по номеру: ";
    it->print();
  } else {
    std::cout << "\nКонтакт не найден.\n";
  }

  return 0;
}
