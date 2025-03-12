#include <iostream>

typedef void *(*FuncPtr)();

void *proxy();

void *selfFunc() { return (void *)&proxy; }

void *proxy() { return (void *)&selfFunc; }

int main() {
  FuncPtr f1 = (FuncPtr)selfFunc();
  FuncPtr f2 = (FuncPtr)f1();

  if (f2 == (void *)&selfFunc) {
    std::cout << "Вернули указатель" << std::endl;
  }

  return 0;
}