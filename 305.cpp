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
    virtual ~Class1() = default;
};

class Class2 : public virtual Shape {
public:
    virtual void func2() const {
        std::cout << "Class2" << std::endl;
    }
    virtual ~Class2() = default;
};

class MultipleInheritance : public Class1, public Class2 {
public:
    void func() {
        std::cout << "MultipleInheritance" << std::endl;
    }
    virtual ~MultipleInheritance() = default;
};

int main() {
    //Down-casting
    Shape* base = new MultipleInheritance();
    
    MultipleInheritance* down = dynamic_cast<MultipleInheritance*>(base);
    if (down) {
        std::cout << "Произвёл down-casting к MultipleInheritance" << std::endl;
        down->func1();
    } else {
        std::cout << "Не смог привести к MultipleInheritance" << std::endl;
    }
/*
    Class2* ptr2 = dynamic_cast<Class2*>(down);
    if (ptr2) {
        ptr2->func2();
    } else {
        std::cout << "Не смог привести к Class2" << std::endl;
    }
*/
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

    //Bad side-casting
    Class1* base1 = new Class1();
    Class2* bad_cast = dynamic_cast<Class2*>(base1);
    if (bad_cast) {
        bad_cast->func2();
    } else {
        std::cout << "Не удалось выполнить side-cast Class1 -> Class2" << std::endl;
    }

    delete base;
    delete side;
    delete base1;
    return 0;
}