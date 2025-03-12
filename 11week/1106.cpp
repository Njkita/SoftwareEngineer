#include <iostream>
#include <vector>
#include <memory>
#include <cmath>

class Circle;
class Square;
class Triangle;

class Visitor {
public:
    virtual void visit(Circle &c) = 0;
    virtual void visit(Square &s) = 0;
    virtual void visit(Triangle &t) = 0;
    virtual ~Visitor() = default;
};

class Shape {
public:
    virtual double getArea() const = 0;
    virtual double getPerimeter() const = 0;
    virtual void accept(Visitor &visitor) = 0;
    virtual ~Shape() = default;
};

class Circle : public Shape {
public:
    static constexpr double PI = 3.14159;
    double radius;

    Circle(double r) : radius(r) {}

    double getArea() const override {
        return PI * radius * radius;
    }

    double getPerimeter() const override {
        return 2 * PI * radius;
    }

    void accept(Visitor &visitor) override {
        visitor.visit(*this);
    }
};

class Square : public Shape {
public:
    double side;

    Square(double s) : side(s) {}

    double getArea() const override {
        return side * side;
    }

    double getPerimeter() const override {
        return 4 * side;
    }

    void accept(Visitor &visitor) override {
        visitor.visit(*this);
    }
};

class Triangle : public Shape {
public:
    double a, b, c;

    Triangle(double x, double y, double z) : a(x), b(y), c(z) {}

    double getArea() const override {
        double s = (a + b + c) / 2;
        return std::sqrt(s * (s - a) * (s - b) * (s - c));
    }

    double getPerimeter() const override {
        return a + b + c;
    }

    void accept(Visitor &visitor) override {
        visitor.visit(*this);
    }
};

class Serializer : public Visitor {
public:
    void visit(Circle &c) override {
        std::cout << "Круг (Радиус: " << c.radius 
                  << ", Площадь: " << c.getArea()
                  << ", Периметр: " << c.getPerimeter() << ")\n";
    }

    void visit(Square &s) override {
        std::cout << "Квадрат (Сторона: " << s.side
                  << ", Площадь: " << s.getArea()
                  << ", Периметр: " << s.getPerimeter() << ")\n";
    }

    void visit(Triangle &t) override {
        std::cout << "Треугольник (Стороны: " << t.a << ", " << t.b << ", " << t.c
                  << ", Площадь: " << t.getArea()
                  << ", Периметр: " << t.getPerimeter() << ")\n";
    }
};

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(5));
    shapes.push_back(std::make_unique<Square>(4));
    shapes.push_back(std::make_unique<Triangle>(3, 4, 5));

    Serializer serializer;

    std::cout << "Сериализация информации о фигурах:\n";
    for (auto &shape : shapes) {
        shape->accept(serializer);
    }

    return 0;
}
