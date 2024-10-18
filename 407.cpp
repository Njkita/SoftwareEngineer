#include <iostream>

template <size_t N> struct Fib {
    static constexpr size_t value = Fib<N - 1>::value + Fib<N - 2>::value;
};

template <> struct Fib <0> {
    static constexpr size_t value = 0;
};

template <> struct Fib <1> {
    static constexpr size_t value = 1;
};

int main() {
    constexpr size_t a = Fib <7>::value;
    constexpr size_t b = Fib <13>::value;
    
    std::cout << "Fib(7) = " << a << std::endl;
    std::cout << "Fib(13) = " << b << std::endl;

    return 0;
}
