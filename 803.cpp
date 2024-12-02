#include <cassert>
#include <iostream>
#include <map>
#include <string>


using namespace std::literals;

enum class Month {
  January = 1,
  February,
  March,
  April,
  May,
  June,
  July,
  August,
  September,
  October,
  November,
  December
};

inline const std::map<Month, std::string> monthNames = {
    {Month::January, "January"},
    {Month::February, "February"},
    {Month::March, "March"},
    {Month::April, "April"},
    {Month::May, "May"},
    {Month::June, "June"},
    {Month::July, "July"},
    {Month::August, "August"},
    {Month::September, "September"},
    {Month::October, "October"},
    {Month::November, "November"},
    {Month::December, "December"}};

inline std::string to_string(Month month) { return monthNames.at(month); }

class Entity {
public:
  Entity() : m_data_1(s_data_1), m_month(Month::January), m_data_3(0) {}

  Entity(const int &data_1, Month month, int data_3 = 0)
      : m_data_1(data_1),
        m_month(month),
        m_data_3(data_3) {}

  ~Entity() { std::clog << "Entity::~Entity\n"; }

  auto data_1() const { return m_data_1; }
  auto data_3() const { return m_data_3; }
  Month month() const { return m_month; }

  const auto &data_as_string() const {
    if (m_cached_data.is_invalid) {
      m_cached_data.update(*this);
    }

    return m_cached_data.string;
  }

  void set_data_3(int data) {
    m_data_3 = data;
    m_cached_data.is_invalid = true;
  }

  static void test() {
    std::clog << "Entity::test : s_data_1 = " << s_data_1 << '\n';
  }

private:
  struct Cached_Data {
    void update(const Entity &entity) {
      string = std::to_string(entity.m_data_1) + '/' +
               to_string(entity.m_month) + '/' +
               std::to_string(entity.m_data_3);

      is_invalid = false;
    }

    std::string string;
    bool is_invalid = true;
  };

  static inline auto s_data_1 = 0;
  const int &m_data_1;
  const Month m_month;
  int m_data_3 = 0;

  mutable Cached_Data m_cached_data;
};

int main() {
  Entity entity_1(0, Month::February, 1);

  assert(entity_1.data_3() == 1);
  assert(entity_1.data_as_string() == "0/February/1");

  const Entity entity_2(1, Month::March);

  assert(entity_2.data_3() == 0);
  assert(entity_2.data_as_string() == "1/March/0");

  Entity entity_3(2, Month::April, 5);
  assert(entity_3.data_as_string() == "2/April/5");

  entity_1.test();
  Entity::test();

  std::cout << "All tests passed.\n";
  return 0;
}