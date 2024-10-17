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
private:
    void func() const override {
        func1();
    }
    virtual void func1() const = 0;
};

class Class2Inheritance : public Class2 {
private:
    void func() const override {
        func2();
    }
    virtual void func2() const = 0;
};

class MultipleInheritance : public Class1Inheritance, public Class2Inheritance {
private:
    void func1() const override  {
        std::cout << "from Class1" << std::endl;
    }

    void func2() const override  {
        std::cout << "from Class2" << std::endl;
    }
};

int main() {
    MultipleInheritance interface_;
    Class1* ptr1 = &interface_;
    Class2* ptr2 = &interface_;
    ptr1->func();
    ptr2->func();
    return 0;
}
    
