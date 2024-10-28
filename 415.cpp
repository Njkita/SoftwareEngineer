#include <iostream>

template < typename ... Ts > struct List {};

template <typename T, typename L> struct Contains;

template <typename T> struct Contains<T, List<>> : std::false_type {};

template <typename T, typename... Ts> 
struct Contains<T, List<T, Ts...>> : std::true_type {};

template <typename T, typename A, typename... Ts>
struct Contains<T, List<A, Ts...>> : Contains<T, List<Ts...>> {};

int main() {
    using MyList = List<int, char, double, size_t>;

    std::cout << "Contains int: " << Contains<int, MyList>::value << std::endl;
    std::cout << "Contains float: " << Contains<float, MyList>::value << std::endl;
    std::cout << "Contains char: " << Contains<size_t, MyList>::value << std::endl;

    return 0;
}