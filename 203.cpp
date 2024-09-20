#include <iostream>
#include <vector>
#include <string>
#include <cmath> 
#include <map>

// Реализуйте алгоритм вычисления всех чисел Армстронга, всех чисел Фибоначчи, всех избыточных чисел и всех
// дружественных чисел, меньших числа N, заданного пользователем.

std::vector<size_t> Divisor(size_t N) {
    std::vector<size_t> divisor_v;
    for (size_t i = 1; i <= std::sqrt(N); ++i) {
        if (N % i == 0) {
            divisor_v.push_back(i);
            if (i != N / i) {
                divisor_v.push_back(N / i);
            }
        }
    }
    return divisor_v;
}

bool Prime(size_t n) {
    if (n == 2 || n == 3) {
        return true;
    }
    if ((n == 1) || (n%2  == 0) || (n%3 == 0)) {
        return false;
    }
    
    for (size_t i = 5; i <= std::sqrt(n); i += 6) {
        if ((n % i == 0) || (n % (i + 2) == 0)) {
            return false;
        }
    }
    return true;
}    



int main() {
    size_t N;
    std::cin >> N;
    
    std::vector<size_t> v = Divisor(N);
    std::vector<size_t> V;
    
    for (short y = 0; y < v.size(); ++y) {
        if (Prime(v[y]) ) {
            V.push_back(v[y]);
        }
    }
    for (short i = 0; i < v.size(); ++i) {
        std::cout << v[i] << " ";
    }
    std::cout << '\n';
    for (short i = 0; i < V.size(); ++i) {
        std::cout << V[i] << " ";
    }
    
    return 0;
}