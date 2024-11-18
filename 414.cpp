#include <type_traits>

template <typename T, typename = std::void_t<>>
struct is_class : std::false_type {};

template <typename T>
struct is_class<T, std::void_t<void (T::*)()>>
    : std::bool_constant<!std::is_union_v<T>> {};

class Class {};
union MyUnion {};

int main() {
  static_assert(is_class<Class>::value, "Class is class");
  static_assert(!is_class<int>::value, "int isn't class");
  static_assert(!is_class<MyUnion>::value, "MyUnion isn't class");
  return 0;
}
