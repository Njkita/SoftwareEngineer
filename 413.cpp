#include <type_traits>

template <typename T> struct decay {
private:
  using U = typename std::remove_reference<T>::type;

public:
  using type = std::conditional_t<
      std::is_array_v<U>,
      std::add_pointer_t<std::remove_extent_t<U>>,
      std::conditional_t<
          std::is_function_v<U>,
          std::add_pointer_t<U>,
          std::remove_cv_t<U>>>;
};

template <typename T> using my_decay_t = typename decay<T>::type;

template <typename T, typename U>
constexpr bool is_decay_equ = std::is_same<my_decay_t<T>, U>::value;

int main() {
  static_assert(is_decay_equ<int, int> && !is_decay_equ<int, float> &&
                is_decay_equ<int &, int> && is_decay_equ<int &&, int> &&
                is_decay_equ<const int &, int> && is_decay_equ<int[2], int *> &&
                !is_decay_equ<int[4][2], int *> &&
                !is_decay_equ<int[4][2], int **> &&
                is_decay_equ<int[4][2], int(*)[2]> &&
                is_decay_equ<int(int), int (*)(int)>);
  return 0;
}
