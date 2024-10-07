#include <iostream>

//Решение проблемы наследования (сиамских  близнецов) посредством внедрения промежуточных классов-посредников

class Class1 {
public:
    virtual void func() const {
        std::cout << "Class1" << std::endl;
    }
};

class Class2 {
public:
    virtual void func() const {
        std::cout << "Class2" << std::endl;
    }
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
public:
    void func1() const {
        Class1Inheritance::func();
    }
    void func2() const {
        Class2Inheritance::func();
    }
};

int main() {
    MultipleInheritance func_;
    func_.func1();
    func_.func2();
    return 0;
}
    
