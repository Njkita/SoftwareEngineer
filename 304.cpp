#include <iostream>

//Решение проблемы наследования (сиамских  близнецов) посредством внедрения промежуточных классов-посредников

class Class1 {
public:
    virtual void func() const {
        std::cout << "Class1" << std::endl;
    }
    virtual ~Class1() = default;
};

class Class2 {
public:
    virtual void func() const {
        std::cout << "Class2" << std::endl;
    }
    virtual ~Class2() = default;
};

class Class1Inheritance : public Class1 {
public:
    void func() const override {
        std::cout << "from Class1" << std::endl;
    }
};

class Class2Inheritance : public Class2 {
public:
    void func() const override {
        std::cout << "from Class2" << std::endl;
    }
};

class MultipleInheritance : public Class1Inheritance, public Class2Inheritance {
/*    
public:
    void func() const override  {
        std::cout << "from MultipleInheritance" << std::endl;
    }
*/
};

int main() {
    MultipleInheritance interface_;
    Class1* ptr1 = &interface_;
    Class2* ptr2 = &interface_;
    ptr1->func();
    ptr2->func();
    return 0;
}
    
