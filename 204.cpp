#include <iostream>
#include <cmath> 
#include <iterator>
#include <algorithm>
#include <numeric>

//Реализуйте алгоритм Евклида в рекурсивном и нерекурсивном виде для вычисления НОД
//Дополнительно реализуйте алгоритм вычисления НОК двух чисел 

size_t GCD(size_t a, size_t b) {
    while (a != 0 && b != 0) {
        a = a%b;
        b = b%a;
    }
    return a+b;
}

size_t GCD_recursion(size_t a, size_t b) {
    if (a == 0 || b == 0) {
        return a+b;
    }
    else {
        return GCD_recursion(b%a, a);   
    }
    
    /*
    size_t max_n = std::max(a, b);
    size_t min_n = std::min(a, b);
    if (min_n == 0) {
        return max_n;
    }
    else {
        //return GCD_recursion(max_n%min_n, min_n);
        
    }
    */
}

size_t LCM(size_t a, size_t b) {
    return abs(a*b)/GCD(a, b);
}


int main()
{
    size_t a, b;
    std::cin >> a >> b;
    std::cout << GCD(a, b) << std::endl;
    std::cout << GCD_recursion(a, b) << std::endl;
    std::cout << "std::gcd " << std::gcd(a, b) << std::endl;
    std::cout << LCM(a, b) << std::endl;
    std::cout << "std::lcm " << std::lcm(a, b) << std::endl; 
}