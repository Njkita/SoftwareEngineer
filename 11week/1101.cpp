#include <iostream>

using FuncPtr = auto(*)() -> FuncPtr;

FuncPtr proxy();

FuncPtr selfFunc() { return &proxy; }

FuncPtr proxy() { return &selfFunc; }

int main() {
    FuncPtr f1 = selfFunc();
    FuncPtr f2 = f1();

    if (f2 == &selfFunc) {
        std::cout << "Вернули указатель" << std::endl;
    }

    return 0;
}
