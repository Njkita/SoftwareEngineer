import geometry;

#include <iostream>

int main() {
  Circle c{{0, 0}, 5.0};
  std::cout << "Area of the circle: " << area(c) << "\n";
  return 0;
}