#include <iostream>
#include <cmath> 
#include <iterator>
#include <algorithm>
#include <numeric>

//Реализуйте алгоритм Евклида в рекурсивном и нерекурсивном виде для вычисления НОД
//Дополнительно реализуйте алгоритм вычисления НОК двух чисел 

int GCD(int a, int b) {
    while (a != 0 && b != 0) {
        if (a > b) {
            a = a%b;
        }
        else {
            b = b%a;
        }
    }
    return a+b;
}

int GCD_recursion(int a, int b) {
    int max_n = std::max(a, b);
    int min_n = std::min(a, b);
    if (min_n == 0) {
        return max_n;
    }
    else {
        return GCD_recursion(max_n%min_n, min_n);
    }
    
}

int LCM(int a, int b) {
    return (abs(a*b))/GCD(a, b);
}


int main()
{
    int a, b;
    std::cin >> a >> b;
    std::cout << GCD(a, b) << std::endl;
    std::cout << GCD_recursion(a, b) << std::endl;
    std::cout << "std::gcd " << std::gcd(a, b) << std::endl;
    std::cout << LCM(a, b) << std::endl;
    std::cout << "std::lcm " << std::lcm(a, b) << std::endl; 
}