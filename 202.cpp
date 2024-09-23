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

size_t Sum (std::vector<size_t> v) {
    size_t sum = 0;
    for (size_t y = 0; y < v.size(); ++y) {
        sum += v[y];
    }
    return sum;
}

std::vector<size_t> Find_Excess(size_t N) {
    std::vector<size_t> excess_number;
    for (size_t k = 1; k < N; ++k) {
        std::vector<size_t> number = Divisor(k);
        size_t sum = Sum(number);
        if (sum-k > k) {
            excess_number.push_back(k); 
        }
    }
    return excess_number;
}    

std::vector<size_t> Find_Friendly(size_t N) {
    std::map<size_t, size_t> sum_number;
    std::vector<size_t> friendly_number;
    
    for (size_t k = 1; k < N; ++k) {
        std::vector<size_t> number = Divisor(k);
        size_t sum = Sum(number)-k;
        sum_number[k] = sum;
        
        if((sum_number[sum] == k) && (sum != k)) {
            friendly_number.push_back(k);
            friendly_number.push_back(sum);
        }
    }
    return friendly_number;
}

std::vector<size_t> Find_Armstrong(size_t N) {
    const short n = (std::to_string(N)).length();
    std::vector<size_t> data;

	for (size_t k = 1; k < N; ++k) {
	    size_t sum = 0;
	    size_t number = k;
        short l = std::to_string(k).length();
        
	    while (number > 0) {
	        int t = number%10;
	        sum += pow (t, l);  //A[t][l] 
	        number /= 10;
	    }
	    
        if (sum == k) {
            data.push_back(k); 
        }
	}
	return data;
}

std::vector<size_t> Find_Fibonacci(size_t N) {
    std::vector<size_t> fibonacci = {0, 1};
        int i = 2;
        while ((fibonacci[i - 1] + fibonacci[i - 2]) < N) {
            fibonacci.push_back(fibonacci[i - 1] + fibonacci[i - 2]);
            i += 1;
        }
    
    return fibonacci;
}    


int main() {
    size_t N;
    std::cin >> N;
    
    //Find_Friendly - дружественные числа
    //Find_Armstrong - числа Армстронга
    //Find_Excess - избыточные числа
    //Find_Fibonacci - числа Фиббоначи
    
    std::vector<size_t> v = Find_Armstrong(N);
    
    for (short y = 0; y < v.size(); ++y) {
        std::cout << v[y] << " ";
    }
    return 0;
}
