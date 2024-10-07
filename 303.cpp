#include <iostream>
#include <cmath>  
#include <numbers>

//иерархия классов, описывающих геометрические фигуры

class Shape {
public: 
    virtual ~Shape() = default;
public:
    virtual double square() const = 0;       
    virtual double perimeter() const = 0;             
};

class Polygon : public virtual Shape {
public:
    Polygon() = default;  
};

class Ellipse : public virtual Shape {
public:
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
    double width, height;
public:
    Rectangle(double w, double h) : width(w), height(h) {}
    double square() const override {
        return width * height;
    }
    double perimeter() const override {
        return 2 * (width + height);
    }
};

class Triangle : public virtual Polygon {
public:
    double a, b, c; 
public:
    Triangle(double side1, double side2, double side3) : a(side1), b(side2), c(side3) {}
    bool truth = ((a*a+b*b >= c*c) && (a*a+c*c >= b*b) && (b*b+c*c >= a*a));
    double square() const override {
        if (truth) {
            double s = perimeter() / 2;
            return std::sqrt(s * (s - a) * (s - b) * (s - c));
        }
        else {
            return 0.0;
        }
    }
    double perimeter() const override {
        if (truth) {
            return a + b + c;
        }
        else {
            return 0.0;
        }
    }
}; //треугольник

class Square : public Rectangle {
public:
    Square(double side) : Rectangle(side, side) {} 
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

    
