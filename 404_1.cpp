#include <iostream>
#include <type_traits>

int sum_() {
    return 0;
}

int get_int(int value) {
    return value;
}

template <typename T>
int get_int(T value) {
    return 0;
}

template <typename T, typename... Ts> 
int sum_(T first, Ts... next) {
    return get_int(first) + sum_(next...);
}

int main() {
    std::cout << sum_(0, 2.54, 13, std::string("string"), 7, 0.25, 'a') << std::endl;
    return 0;
}  
