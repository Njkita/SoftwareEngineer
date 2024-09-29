#include <iostream>
#include <vector>
#include <string>
#include <cmath> 
#include <map>
#include <iterator>
#include <algorithm>

//Реализуйте алгоритм вычисления всех простых множителей некоторого числа, заданного пользователем

std::vector<int> Catch(std::vector<int> v, int n) {
    if (std::find(v.begin(), v.end(), n) == v.end()) {
        v.push_back(n);
    }
    return v;
}

std::vector<int> prime_factors(int n) {
    std::vector<int> factors;
    while (n % 2 == 0) {
        factors = Catch(factors, 2);
        
        n = n / 2;
    }

    for (int i = 3; i <= std::sqrt(n); i += 2) {
        while (n%i == 0) {
            factors = Catch(factors, i);
            n = n / i;
        }
    }

    if (n > 2) {
        factors = Catch(factors, n);
    }
    return factors;
}

int main()
{
    int number = 0;
    std::cin >> number;
    auto factors = prime_factors(number);
    std::copy(std::begin(factors), std::end(factors),
    std::ostream_iterator<int>(std::cout, " "));
}