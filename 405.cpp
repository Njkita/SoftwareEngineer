#include <iostream>

template <typename T> T get_min(T value) {
        return value;
}

template <typename T, typename... Ts> 
T get_min(T value, Ts... other) {
    T min_ = get_min(other...);  
    return (value < min_) ? value : min_;
}

int main() {
    std::cout << get_min (5, 2, 19, 0, 45, -7, 4) << std::endl;
    std::cout << get_min (5.4, 2.0, 19.89, 0.0, 45.5, -7.311, 4.6) << std::endl;
    return 0;
} 
