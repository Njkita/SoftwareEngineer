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
        if (a == 0 && b == 0 && c == 0) {
            throw std::invalid_argument("a, b, c can't be zero");
        }
    }
    friend std::ostream &operator<<(std::ostream &os, const Line &line) {
        os << line.a << "x + " << line.b << "y + " << line.c << " = 0";
        return os;
    }
};

using Intersection = std::variant<std::monostate, Point, Line>;

Intersection Intersect_(const Line &l1, const Line &l2) {
    double d = l1.a * l2.b - l2.a * l1.b;

    if (d == 0.0) {
        if (l1.a * l2.c == l2.a * l1.c) {
            return l1;
        } else {
            return std::monostate{};
        }
    } else {
        double x = (l1.b * l2.c - l2.b * l1.c) / d;
        double y = (l2.a * l1.c - l1.a * l2.c) / d;
        return Point(x, y);
    }
}

struct IntersectionPrinter {
    void operator()(const std::monostate&) const {
        std::cout << "No intersection (the lines are parallel)" << std::endl;
    }

    void operator()(const Point& point) const {
        std::cout << "Intersection at: " << point << std::endl;
    }

    void operator()(const Line& line) const {
        std::cout << "The lines coincide: " << line << std::endl;
    }
};

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
        std::visit(IntersectionPrinter{}, result);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}