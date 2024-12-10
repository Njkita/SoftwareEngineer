#include <boost/rational.hpp>
#include <cassert>
#include <cmath>
#include <iostream>
#include <istream>
#include <numeric>
#include <ostream>
#include <stdexcept>

class Ratio {
public:
  explicit Ratio(int num = 0, int den = 1) : m_num(num), m_den(den) {
    if (m_den == 0) {
      throw std::invalid_argument("Ratio::Ratio: Denominator cannot be zero.");
    }
    if (m_den < 0) {
      m_num *= -1;
      m_den *= -1;
    }
    reduce();
  }

  explicit operator double() const { return 1.0 * m_num / m_den; }

private:
  void reduce() {
    auto gcd = std::gcd(m_num, m_den);
    m_num /= gcd;
    m_den /= gcd;
  }

public:
  friend auto &operator>>(std::istream &stream, Ratio &ratio) {
    int num;
    char c;
    int den;

    stream >> num >> c >> den;

    if (stream.fail() || c != '/') {
      throw std::runtime_error(
          "operator>>: invalid input ('num/den')");
    }

    ratio = Ratio(num, den);
    return stream;
  }

  friend auto &operator<<(std::ostream &stream, const Ratio &ratio) {
    return stream << ratio.m_num << '/' << ratio.m_den;
  }

  auto &operator+=(const Ratio &other) {
    auto lcm = std::lcm(m_den, other.m_den);
    m_num = m_num * (lcm / m_den) + other.m_num * (lcm / other.m_den);
    m_den = lcm;
    reduce();
    return *this;
  }

  auto &operator+=(int value) {
    return *this += Ratio(value);
  }

  auto &operator-=(const Ratio &other) {
    return *this += Ratio(-other.m_num, other.m_den);
  }

  auto &operator-=(int value) {
    return *this += Ratio(-value);
  }

  auto &operator*=(const Ratio &other) {
    m_num *= other.m_num;
    m_den *= other.m_den;
    reduce();
    return *this;
  }

  auto &operator/=(const Ratio &other) {
    if (other.m_num == 0) {
      throw std::domain_error("Ratio::operator/=: division by 0");
    }
    return *this *= Ratio(other.m_den, other.m_num);
  }

  const auto operator++(int) {
    auto copy(*this);
    *this += 1;
    return copy;
  }
  auto &operator++() {
    *this += 1;
    return *this;
  }
  const auto operator--(int) {
    auto copy(*this);
    *this -= 1;
    return copy;
  }
  auto &operator--() {
    *this -= 1;
    return *this;
  }

private:
  int m_num = 0;
  int m_den = 1;
};

auto operator+(const Ratio &lhs, const Ratio &rhs) { return Ratio(lhs) += rhs; }
auto operator-(const Ratio &lhs, const Ratio &rhs) { return Ratio(lhs) -= rhs; }
auto operator*(const Ratio &lhs, const Ratio &rhs) { return Ratio(lhs) *= rhs; }
auto operator/(const Ratio &lhs, const Ratio &rhs) { return Ratio(lhs) /= rhs; }

auto operator<(const Ratio &lhs, const Ratio &rhs) {
  return static_cast<double>(lhs) < static_cast<double>(rhs);
}
auto operator>(const Ratio &lhs, const Ratio &rhs) { return rhs < lhs; }
auto operator<=(const Ratio &lhs, const Ratio &rhs) { return !(lhs > rhs); }
auto operator>=(const Ratio &lhs, const Ratio &rhs) { return !(lhs < rhs); }
auto operator==(const Ratio &lhs, const Ratio &rhs) {
  return !(lhs < rhs) && !(rhs < lhs);
}

auto equal(double x, double y, double epsilon = 1e-6) {
  return std::abs(x - y) < epsilon;
}

int main() {
  try {
    Ratio r1(1, 2);
    Ratio r2(3, 4);
    Ratio r3;
    std::cin >> r3;

    std::cout << "r1: " << r1 << "\n";
    std::cout << "r2: " << r2 << "\n";
    std::cout << "r3: " << r3 << "\n";

    auto r4 = r1 / r2;
    std::cout << "r1 / r2: " << r4 << "\n";

    Ratio r5(1, 0);
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << "\n";
  }

  return 0;
}
