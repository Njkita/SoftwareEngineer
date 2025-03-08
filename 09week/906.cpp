#include <boost/noncopyable.hpp>
#include <cassert>
#include <cstddef>
#include <type_traits>
#include <utility>

///////////////////////////////////////////////////////////////////////////////////

namespace detail {
class Controller : private boost::noncopyable {
public:
  void increase() { ++m_counter; }

  void decrease() {
    if (--m_counter == 0) {
      clear();
    }
  }

protected:
  Controller() = default;
  virtual ~Controller() = default;

private:
  virtual void clear() = 0;

  std::size_t m_counter = 0;
};
} // namespace detail

///////////////////////////////////////////////////////////////////////////////////

namespace detail {
template <typename T> class Handler : public Controller {
public:
  explicit Handler(T *ptr) : m_data(ptr) { increase(); }

private:
  void clear() override {
    delete m_data;
    delete this;
  }

  T *m_data = nullptr;
};
} // namespace detail

///////////////////////////////////////////////////////////////////////////////////

template <typename T> class Shared {
public:
  Shared(T *ptr = nullptr) : m_data(ptr) {
    if (m_data) {
      m_controller = new detail::Handler<T>(m_data);
    }
  }

  Shared(const Shared<T> &other)
      : m_data(other.m_data), m_controller(other.m_controller) {
    if (m_controller) {
      m_controller->increase();
    }
  }

  Shared(Shared<T> &&other) noexcept : Shared() { swap(other); }

  auto &operator=(const Shared &other) {
    Shared(other).swap(*this);
    return *this;
  }

  auto &operator=(Shared &&other) noexcept {
    Shared(std::move(other)).swap(*this);
    return *this;
  }

  template <typename U> friend class Shared;

  template <typename U>
  requires(std::is_convertible_v<U *, T *>)
  Shared(Shared<U> &&other) noexcept
      : m_data(other.m_data), m_controller(other.m_controller) {
    other.m_data = nullptr;
    other.m_controller = nullptr;
  }

  template <typename U>
  requires(std::is_convertible_v<U *, T *>)
  auto &operator=(Shared<U> &&other) noexcept {
    if (this != &other) {
      if (m_controller) {
        m_controller->decrease();
      }
      m_data = other.m_data;
      m_controller = other.m_controller;
      other.m_data = nullptr;
      other.m_controller = nullptr;
    }
    return *this;
  }

  ~Shared() {
    if (m_controller) {
      m_controller->decrease();
    }
  }

  void swap(Shared &other) noexcept {
    std::swap(m_data, other.m_data);
    std::swap(m_controller, other.m_controller);
  }

  auto &operator*() const { return *m_data; }
  auto operator->() const noexcept { return m_data; }
  auto get() const noexcept { return m_data; }
  explicit operator bool() const noexcept { return m_data != nullptr; }

private:
  T *m_data = nullptr;
  detail::Controller *m_controller = nullptr;
};

///////////////////////////////////////////////////////////////////////////////////

struct Base {
  virtual ~Base() = default;
  virtual int getValue() const { return 42; }
};

struct Derived : Base {
  int getValue() const override { return 100; }
};

///////////////////////////////////////////////////////////////////////////////////

int main() {
  {
    Shared<int> shared_1;
    Shared<int> shared_2(new auto(2));
    Shared<int> shared_3(shared_2);
    Shared<int> shared_4(std::move(shared_3));

    shared_3 = shared_2;
    shared_4 = std::move(shared_3);
  }

  { assert(*Shared<int>(new auto(1)) == 1); }

  {
    Shared<Derived> derived_shared(new Derived());

    Shared<Base> base_shared(std::move(derived_shared));

    assert(base_shared->getValue() == 100);
  }

  return 0;
}
