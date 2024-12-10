#include <chrono>
#include <iomanip>
#include <iostream>

int main() {
  int year1, month1, day1;
  int year2, month2, day2;
  std::cin >> year1 >> month1 >> day1;
  std::cin >> year2 >> month2 >> day2;

  try {
    std::chrono::year_month_day date1 =
        std::chrono::year{year1} / month1 / day1;
    std::chrono::year_month_day date2 =
        std::chrono::year{year2} / month2 / day2;

    std::chrono::sys_days days1{date1};
    std::chrono::sys_days days2{date2};

    auto delta = days2 - days1;
    std::cout << delta.count() << " дней\n";
  } catch (const std::exception &e) {
    std::cerr << "Неверный ввод" << e.what() << "\n";
  }

  return 0;
}
