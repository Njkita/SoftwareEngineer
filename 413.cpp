#include <type_traits>

template <typename T>
struct decay {
    using type = typename std::remove_cv<typename std::remove_reference<T>::type>::type;
};

template <typename T, std::size_t N>
struct decay<T[N]> {
    using type = T*;
};

template <typename Ret, typename... Args>
struct decay<Ret(Args...)> {
    using type = Ret(*)(Args...);
};

template <typename Ret, typename... Args>
struct decay<Ret(Args..., ...)> {
    using type = Ret(*)(Args..., ...);
};

int main() {
    static_assert(std::is_same<decay<int>::type, int>::value);
    static_assert(std::is_same<decay<const int&>::type, int>::value);
    static_assert(std::is_same<decay<int[5]>::type, int*>::value);
    static_assert(std::is_same<decay<int(int)>::type, int(*)(int)>::value);

    return 0;
}