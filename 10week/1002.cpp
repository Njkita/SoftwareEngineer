#include <iostream>
#include <limits>
#include <vector>

int main() {
  std::vector<int> vec;
  size_t prev_capacity = vec.capacity();

  // Ёмкость вектора при нехватке памяти
  for (int i = 0; i < 100; ++i) {
    vec.push_back(i);
    size_t new_capacity = vec.capacity();
    if (new_capacity != prev_capacity) {
      std::cout << "Размер: " << vec.size() << ", Емкость: " << new_capacity
                << ", Коэфф. роста: "
                << (prev_capacity > 0 ? (double)new_capacity / prev_capacity
                                      : 0)
                << std::endl;
      prev_capacity = new_capacity;
    }
  }

  // Ёмкость вектора во время работы reserve
  std::cout << "\n-------------------" << std::endl;
  std::vector<int> reserved_vec;
  reserved_vec.reserve(10);
  std::cout << "Начальная емкость после reserve 10: " << reserved_vec.capacity()
            << std::endl;
  reserved_vec.reserve(20);
  std::cout << "Емкость после reserve 20: " << reserved_vec.capacity()
            << std::endl;
  reserved_vec.reserve(15);
  std::cout << "Емкость после reserve 15 - не уменьшается: "
            << reserved_vec.capacity() << std::endl;

  // Выделение памяти в предельном случае
  std::cout << "\n-------------------" << std::endl;
  try {
    std::vector<int> large_vec;
    large_vec.reserve(std::numeric_limits<size_t>::max() / sizeof(int));
  } catch (const std::exception &e) {
    std::cerr << "Ошибка выделения памяти: " << e.what() << std::endl;
  }

  return 0;
}
