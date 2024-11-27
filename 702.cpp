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
          "a, b can't both be zero");
    }
  }
};

using Intersection = std::variant<std::monostate, Point, std::string>;

Intersection Intersect_(const Line &l1, const Line &l2) {
  double d = l1.a * l2.b - l2.a * l1.b;

  if (d == 0.0) {
    if (l1.a * l2.c == l2.a * l1.c && l1.b * l2.c == l2.b * l1.c) {
      return "the straight lines coincided";
    } else {
      return std::monostate{};
    }
  } else {
    double x = (l1.b * l2.c - l2.b * l1.c) / d;
    double y = (l2.a * l1.c - l1.a * l2.c) / d;
    return Point(x, y);
  }
}

void printIntersect(const Intersection &intersection) {
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
    std::cout << "1 straight line (a1, b1, c1): ";
    std::cin >> a1 >> b1 >> c1;
    std::cout << "2 straight line (a2, b2, c2): ";
    std::cin >> a2 >> b2 >> c2;

    Line l1(a1, b1, c1);
    Line l2(a2, b2, c2);

    Intersection result = Intersect_(l1, l2);
    printIntersect(result);
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }

  return 0;
}
