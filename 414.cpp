#include <type_traits>

template <typename T> struct is_class {
 private:
    template <typename A>
    static char test(void (A::*)());

    template <typename A>
    static int test(...);

 public:
    static constexpr bool value = sizeof(test<T>(0)) == sizeof(char);
};

class Class {};

int main() {
    static_assert(is_class<Class>::value, "Class is class");
    static_assert(!is_class<int>::value, "int isn't class");
    return 0;
}