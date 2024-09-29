#include <iostream>
#include <cmath> 
#include <iterator>
#include <algorithm>
#include <numeric>

//Реализуйте алгоритм классификации введенных пользователем символов. Выделите четыре следующих класса: десятичная цифра – 10 символов, арифметический оператор – 4 символа, круглая скобка – 2 символа,
//остальные символы. Используйте ветвление типа switch с проваливанием для избежания дублирования кода.
 

void classifyChar(char A) {
    switch (A) {
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            std::cout << A << " - десятичная цифра" << std::endl;
            break;

        case '+': case '-': case '*': case '/':
            std::cout << A << " - арифметический оператор" << std::endl;
            break;

        case '(': case ')':
            std::cout << A << " - круглая скобка" << std::endl;
            break;

        default:
            std::cout << A << " - остальные символы" << std::endl;
            break;
    }
}

int main() {
    char a;
    std::cin >> a;
    classifyChar(a);
}