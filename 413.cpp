#include <type_traits>

template <typename T>
struct decay {
    using type = typename std::remove_cv<typename std::remove_reference<T>::type>::type;
};

template <typename T, std::size_t n>
struct decay<T[n]> {
    using type = T*;
};

template <typename T, typename... Ts>
struct decay<T(Ts...)> {
    using type = T(*)(Ts...);
};

template <typename T, typename... Ts>
struct decay<T(Ts..., ...)> {
    using type = T(*)(Ts..., ...);
};

int main() {
    static_assert(std::is_same<decay<int>::type, int>::value);
    static_assert(std::is_same<decay<const int&>::type, int>::value);
    static_assert(std::is_same<decay<int[3]>::type, int*>::value);
    static_assert(std::is_same<decay<int(int)>::type, int(*)(int)>::value);

    return 0;
}