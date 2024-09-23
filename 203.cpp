#include <iostream>
#include <vector>
#include <string>
#include <cmath> 
#include <map>
#include <iterator>
#include <algorithm>

std::vector<size_t> Catch(std::vector<size_t> v, size_t n) {
    if (std::find(v.begin(), v.end(), n) == v.end()) {
        v.push_back(n);
    }
    return v;
}

std::vector<size_t> prime_factors(size_t n) {
    std::vector<size_t> factors;
    while (n % 2 == 0) {
        factors = Catch(factors, 2);
        
        n = n / 2;
    }

    for (size_t i = 3; i <= std::sqrt(n); i += 2) {
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
    size_t number = 0;
    std::cin >> number;
    auto factors = prime_factors(number);
    std::copy(std::begin(factors), std::end(factors),
    std::ostream_iterator<size_t>(std::cout, " "));
}
