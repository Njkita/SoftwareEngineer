#include <cmath>
#include <iostream>
#include <memory>
#include <vector>

// Паттерн Visitor - можно использовать для обработки различных геометрических фигур

class Circle;
class Rectangle;
class Triangle;

class Visitor {
public:
  virtual void visit(Circle &c) = 0;
  virtual void visit(Rectangle &r) = 0;
  virtual void visit(Triangle &t) = 0;
  virtual ~Visitor() = default;
};

class Shape {
public:
  virtual void accept(Visitor &visitor) = 0;
  virtual ~Shape() = default;
};

class Circle : public Shape {
public:
  double radius;
  Circle(double r) : radius(r) {}
  void accept(Visitor &visitor) override { visitor.visit(*this); }
};

class Rectangle : public Shape {
public:
  double width, height;
  Rectangle(double w, double h) : width(w), height(h) {}
  void accept(Visitor &visitor) override { visitor.visit(*this); }
};

class Triangle : public Shape {
public:
  double a, b, c;
  Triangle(double x, double y, double z) : a(x), b(y), c(z) {}
  void accept(Visitor &visitor) override { visitor.visit(*this); }
};

class Area_ : public Visitor {
public:
  void visit(Circle &c) override {
    double area = 3.14159 * c.radius * c.radius;
    std::cout << "Площадь круга: " << area << std::endl;
  }
  void visit(Rectangle &r) override {
    double area = r.width * r.height;
    std::cout << "Площадь прямоугольника: " << area << std::endl;
  }
  void visit(Triangle &t) override {
    double s = (t.a + t.b + t.c) / 2;
    double area = std::sqrt(s * (s - t.a) * (s - t.b) * (s - t.c));
    std::cout << "Площадь треугольника: " << area << std::endl;
  }
};

class Renderer_ : public Visitor {
public:
  void visit(Circle &c) override {
    std::cout << "Отрисовка круга с радиусом " << c.radius << std::endl;
  }
  void visit(Rectangle &r) override {
    std::cout << "Отрисовка прямоугольника " << r.width << "x" << r.height
              << std::endl;
  }
  void visit(Triangle &t) override {
    std::cout << "Отрисовка треугольника со сторонами " << t.a << ", " << t.b
              << ", " << t.c << std::endl;
  }
};

int main() {
  std::vector<std::unique_ptr<Shape>> shapes;
  shapes.push_back(std::make_unique<Circle>(5));
  shapes.push_back(std::make_unique<Rectangle>(3, 4));
  shapes.push_back(std::make_unique<Triangle>(3, 4, 5));

  Area_ areaVisitor;
  Renderer_ renderVisitor;

  std::cout << "Вычисление площади" << std::endl;
  for (auto &shape : shapes) {
    shape->accept(areaVisitor);
  }

  std::cout << "\nОтрисовка фигур" << std::endl;
  for (auto &shape : shapes) {
    shape->accept(renderVisitor);
  }

  return 0;
}
