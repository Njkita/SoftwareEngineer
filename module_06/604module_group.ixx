export module geometry;

namespace shapes {
struct Point {
  double x, y;
};

struct Circle {
  Point center;
  double radius;
};

double area(const Circle &c) { return 3.14159 * c.radius * c.radius; }
} // namespace shapes

export using namespace shapes;