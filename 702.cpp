#include <iostream>
#include <optional>
#include <stdexcept>
#include <variant>


class Point {
public:
  double x, y;
  Point(double x, double y) : x(x), y(y) {}
  friend std::ostream &operator<<(std::ostream &os, const Point &point) {
    os << "(" << point.x << ", " << point.y << ")";
    return os;
  }
};

class Line {
public:
  double a, b, c;
  Line(double a, double b, double c) : a(a), b(b), c(c) {
    if (a == 0 && b == 0) {
      throw std::invalid_argument(
          "Invalid line coefficients: a and b cannot both be zero.");
    }
  }
};

using Intersection = std::variant<std::monostate, Point, std::string>;

Intersection Intersect_(const Line &l1, const Line &l2) {
  double determinant = l1.a * l2.b - l2.a * l1.b;

  if (determinant == 0.0) {
    // Проверяем, совпадают ли прямые
    if (l1.a * l2.c == l2.a * l1.c && l1.b * l2.c == l2.b * l1.c) {
      return "Infinite intersections (the lines coincide)";
    } else {
      return std::monostate{}; // Прямые параллельны
    }
  } else {
    // Одна точка пересечения
    double x = (l1.b * l2.c - l2.b * l1.c) / determinant;
    double y = (l2.a * l1.c - l1.a * l2.c) / determinant;
    return Point(x, y);
  }
}

// Функция для вывода результата пересечения
void printIntersection(const Intersection &intersection) {
  if (std::holds_alternative<std::monostate>(intersection)) {
    std::cout << "No intersection (the lines are parallel)" << std::endl;
  } else if (std::holds_alternative<Point>(intersection)) {
    std::cout << "Intersection at: " << std::get<Point>(intersection)
              << std::endl;
  } else if (std::holds_alternative<std::string>(intersection)) {
    std::cout << std::get<std::string>(intersection) << std::endl;
  }
}

int main() {
  try {
    double a1, b1, c1, a2, b2, c2;
    std::cout << "First line a1, b1, c1: ";
    std::cin >> a1 >> b1 >> c1;
    std::cout << "Second line a2, b2, c2: ";
    std::cin >> a2 >> b2 >> c2;

    Line l1(a1, b1, c1);
    Line l2(a2, b2, c2);

    Intersection result = Intersect_(l1, l2);
    printIntersection(result);
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  return 0;
}
