#include <boost/noncopyable.hpp>
#include <cassert>
#include <type_traits>
#include <utility>
#include <iostream>

/////////////////////////////////////////////////////////////////////////

template <typename T>
class Unique : private boost::noncopyable {
public:
  Unique(T *ptr = nullptr) : m_data(ptr) {}

  Unique(Unique &&other) noexcept : Unique() { swap(other); }

  auto &operator=(Unique &&other) noexcept {
    if (this != &other) {
      reset(other.release());
    }
    return *this;
  }

  template <typename U> requires(std::is_convertible_v<U *, T *>)
  Unique(Unique<U> &&other) noexcept : m_data(other.release()) {}

  template <typename U> requires(std::is_convertible_v<U *, T *>)
  auto &operator=(Unique<U> &&other) noexcept {
    reset(other.release());
    return *this;
  }

  ~Unique() { reset(); }

  void swap(Unique &other) noexcept { std::swap(m_data, other.m_data); }

  T *release() noexcept { return std::exchange(m_data, nullptr); }

  void reset(T *ptr = nullptr) noexcept {
    if (m_data) {
      delete m_data;
    }
    m_data = ptr;
  }

  T &operator*() const { return *m_data; }

  T *operator->() const noexcept { return m_data; }

  T *get() const noexcept { return m_data; }

  explicit operator bool() const noexcept { return m_data != nullptr; }

private:
  T *m_data = nullptr;
};

/////////////////////////////////////////////////////////////////////////

template <typename T, typename... Ts>
auto make_unique(Ts &&...xs) {
  return Unique<T>(new T(std::forward<Ts>(xs)...));
}

/////////////////////////////////////////////////////////////////////////

struct Base {
  virtual ~Base() = default;
  virtual int getValue() const { return 92; }
};

struct Derived : Base {
  int getValue() const override { return 100; }
};

/////////////////////////////////////////////////////////////////////////

int main() {
  {
    Unique<int> unique_1;
    Unique<int> unique_2(new int(2));
    Unique<int> unique_3(new int(3));
    Unique<int> unique_4(std::move(unique_3));
    unique_3.reset(new int(3));
    unique_4 = std::move(unique_3);
  }

  { assert(*make_unique<int>(1) == 1); }

  {
    Unique<Derived> derived_unique(new Derived());
    Unique<Base> base_unique(std::move(derived_unique));
    assert(base_unique->getValue() == 100);
  }

  // Дополнительные тесты для операторов присваивания
  {
    Unique<int> u1(new int(42));
    Unique<int> u2;
    u2 = std::move(u1);
    assert(u1.get() == nullptr);
    assert(*u2 == 42);
  }

  {
    Unique<Derived> uDerived(new Derived());
    Unique<Base> uBase;
    uBase = std::move(uDerived);
    assert(uDerived.get() == nullptr);
    assert(uBase->getValue() == 100);
  }

  std::cout << "All tests passed!" << std::endl;
  return 0;
}
