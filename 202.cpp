#include <iostream>
#include <vector>
#include <string>
#include <cmath> 
#include <map>

// Реализуйте алгоритм вычисления всех чисел Армстронга, всех чисел Фибоначчи, всех избыточных чисел и всех
// дружественных чисел, меньших числа N, заданного пользователем.

std::vector<int> Divisor(int N) {
    std::vector<int> divisor_v;
    for (int i = 1; i <= std::sqrt(N); ++i) {
        if (N % i == 0) {
            divisor_v.push_back(i);
            if (i != N / i) {
                divisor_v.push_back(N / i);
            }
        }
    }
    return divisor_v;
}

int Sum (std::vector<int> v) {
    int sum = 0;
    for (int y = 0; y < v.size(); ++y) {
        sum += v[y];
    }
    return sum;
}

std::vector<int> Find_Excess(int N) {
    std::vector<int> excess_number;
    for (int k = 1; k < N; ++k) {
        std::vector<int> number = Divisor(k);
        int sum = Sum(number);
        if (sum-k > k) {
            excess_number.push_back(k); 
        }
    }
    return excess_number;
}    

std::vector<int> Find_Friendly(int N) {
    std::map<int, int> sum_number;
    std::vector<int> friendly_number;
    
    for (int k = 1; k < N; ++k) {
        std::vector<int> number = Divisor(k);
        int sum = Sum(number)-k;
        sum_number[k] = sum;
        
        if((sum_number[sum] == k) && (sum != k)) {
            friendly_number.push_back(k);
            friendly_number.push_back(sum);
        }
    }
    return friendly_number;
}

std::vector<int> Find_Armstrong(int N) {
    const short n = (std::to_string(N)).length();
    std::vector<int> data;

	for (int k = 1; k < N; ++k) {
	    int sum = 0;
	    int number = k;
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

std::vector<int> Find_Fibonacci(int N) {
    std::vector<int> fibonacci = {0, 1};
        int i = 2;
        while ((fibonacci[i - 1] + fibonacci[i - 2]) < N) {
            fibonacci.push_back(fibonacci[i - 1] + fibonacci[i - 2]);
            i += 1;
        }
    
    return fibonacci;
}    


int main() {
    int N;
    std::cin >> N;
    
    //Find_Friendly - дружественные числа
    //Find_Armstrong - числа Армстронга
    //Find_Excess - избыточные числа
    //Find_Fibonacci - числа Фиббоначи
    
    std::vector<int> v = Find_Armstrong(N);
    
    for (short y = 0; y < v.size(); ++y) {
        std::cout << v[y] << " ";
    }
    return 0;
}