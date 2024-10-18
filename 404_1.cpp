#include <iostream>
#include <type_traits>

int sum_() {
    return 0;
}

template <typename T>
int get_int(T value) {
    if constexpr (std::is_same_v<T, int>) {
        return value;
    } else {
        return 0;
    }
}

template <typename T, typename... Ts> 
int sum_(T first, Ts... next) {
    return get_int(first) + sum_(next...);  // Суммируем только целые
}

int main() {
    std::cout << sum_(0, 2.54, 13, std::string("string"), 7, 0.25, 'a') << std::endl;
    return 0;
}    
