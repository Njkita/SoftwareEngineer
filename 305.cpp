#include <iostream>
#include <typeinfo>

class Shape {
public:
    virtual ~Shape() = default;  
};

class Class1 : public virtual Shape {
public:
    virtual void func1() const {
        std::cout << "Class1" << std::endl;
    }
};

class Class2 : public virtual Shape {
public:
    virtual void func2() const {
        std::cout << "Class2" << std::endl;
    }
};

class MultipleInheritance : public Class1, public Class2 {
public:
    void func() {
        std::cout << "MultipleInheritance" << std::endl;
    }
};

int main() {
    //Down-casting
    Shape* down = new MultipleInheritance();
    Class1* ptr1 = dynamic_cast<Class1*>(down);
    if (ptr1) {
        ptr1->func1();
    } else {
        std::cout << "Не смог привести к Class1" << std::endl;
    }

    Class2* ptr2 = dynamic_cast<Class2*>(down);
    if (ptr2) {
        ptr2->func2();
    } else {
        std::cout << "Не смог привести к Class2" << std::endl;
    }

    //Side-casting
    MultipleInheritance* side = new MultipleInheritance();
    Class1* ptr1_ = dynamic_cast<Class1*>(side);
    if (ptr1_) {
        ptr1_->func1();
    }

    Class2* ptr2_ = dynamic_cast<Class2*>(side);
    if (ptr2_) {
        ptr2_->func2();
    }

    delete down;
    delete side;
    return 0;
}