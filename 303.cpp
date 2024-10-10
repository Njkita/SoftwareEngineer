#include <iostream>
#include <cmath>  
#include <numbers>
#include <vector>

//иерархия классов, описывающих геометрические фигуры

class Shape {
public: 
    virtual ~Shape() = default;
    virtual double square() const = 0;       
    virtual double perimeter() const = 0;             
};

class Polygon : public virtual Shape {
protected:
    std::vector<double> sides;
public:
    Polygon() = default;
    Polygon(const std::vector<double>& sides_) : sides(sides_) {}
    
    double perimeter() const override {
        double p = 0;
        for (double side : sides) {
            p += side;
        }
        return p;
    }  
};

class Ellipse : public virtual Shape {
protected:
    double semi_major_axis, semi_minor_axis;
    const double PI = 3.14159265358979;
public:
    Ellipse(double a, double b) : semi_major_axis(a), semi_minor_axis(b) {}
    double square() const override {
        return PI * semi_major_axis * semi_minor_axis;
    }
    double perimeter() const override {
        return 4 * (PI * semi_major_axis * semi_minor_axis + pow(2, (semi_major_axis - semi_minor_axis))) / (semi_major_axis + semi_minor_axis);
    }
};

class Rectangle : public virtual Polygon {
public:
    Rectangle(double w, double h) : Polygon({w, h, w, h}) {}
    double square() const override {
        return sides[0] * sides[1];
    }
};

class Triangle : public virtual Polygon {
public:
    Triangle(double side1, double side2, double side3) : Polygon({side1, side2, side3}) {}
    
    double square() const override {
        double s = perimeter() / 2;
        return std::sqrt(s * (s - sides[0]) * (s - sides[1]) * (s - sides[2]));
    }
}; 

class Square : public Rectangle {
public:
    Square(double side) : Rectangle(side, side) {
        sides = {side, side, side, side};
    } 
}; 

class Circle : public Ellipse {
public:
    Circle(double radius) : Ellipse(radius, radius) {}  
};


int main() {
    Rectangle rect(5.0, 12.0);
    Square square(7.0);
    Triangle triangle(12.0, 9.0, 13.0);
    Ellipse ellipse(4.0, 2.0);
    Circle circle(3.0);

    std::cout << "Площадь прямоугольника: " << rect.square() << ", периметр прямоугольника: " << rect.perimeter() << std::endl;
    std::cout << "Площадь квадрата: " << square.square() << ", периметр квадрата: " << square.perimeter() << std::endl;
    std::cout << "Площадь треугольника: " << triangle.square() << ", периметр треугольника: " << triangle.perimeter() << std::endl;
    std::cout << "Площадь эллипса: " << ellipse.square() << ", периметр эллипса: " << ellipse.perimeter() << std::endl;
    std::cout << "Площадь окружности: " << circle.square() << ", периметр окружности: " << circle.perimeter() << std::endl;

    return 0;
}

    
