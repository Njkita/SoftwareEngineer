#include <cctype>
#include <cmath>
#include <exception>
#include <iostream>
#include <istream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <variant>

class Stream {
public:
  using token_t = std::variant<char, double, std::string>;

  Stream(const std::string &string) : m_stream(string + ';') {}

  auto empty() { return m_stream.peek() == ';'; }

  auto get() {
    if (m_has_token) {
      m_has_token = false;
      return m_token;
    }

    char x = '\0';
    m_stream >> x;

    switch (x) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case '!':
    case '(':
    case ')':
    case '[':
    case ']':
    case '{':
    case '}':
    case ';':
      return token_t(x);

    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '.':
      m_stream.unget();
      double y;
      m_stream >> y;
      return token_t(y);

    default:
      std::string str(1, x);
      while (m_stream.get(x) && (std::isalpha(x) || std::isdigit(x)))
        str += x;

      if (!std::isspace(x))
        m_stream.unget();

      return token_t(str);
    }
  }

  void putback(const token_t &token) {
    m_token = token;
    m_has_token = true;
  }

private:
  std::stringstream m_stream;
  token_t m_token;
  bool m_has_token = false;
};

class Calculator {
public:
  void test() {
    std::string string;
    std::cout << "Calculator::test : enter expression(s): \n";

    while (std::getline(std::cin >> std::ws, string)) {
      if (Stream stream(string); !stream.empty()) {
        try {
          std::cout << "Calculator::test : " << string << " = "
                    << statement(stream) << '\n';
        } catch (const std::exception &e) {
          std::cout << "Error: " << e.what() << '\n';
        }
      } else {
        break;
      }
    }
  }

private:
  double statement(Stream &stream) {
    auto token = stream.get();

    if (std::holds_alternative<std::string>(token)) {
      if (std::get<std::string>(token) == "set")
        return declaration(stream);
    }

    stream.putback(token);
    return expression(stream);
  }

  double declaration(Stream &stream) {
    auto name = std::get<std::string>(stream.get());
    m_variables[name] = expression(stream);
    return m_variables[name];
  }

  double expression(Stream &stream) {
    double x = term(stream);
    auto token = stream.get();

    while (true) {
      if (!std::holds_alternative<char>(token)) {
        stream.putback(token);
        return x;
      }

      switch (std::get<char>(token)) {
      case '+':
        x += term(stream);
        break;
      case '-':
        x -= term(stream);
        break;
      default:
        stream.putback(token);
        return x;
      }

      token = stream.get();
    }
  }

  double term(Stream &stream) {
    double x = factor(stream);
    auto token = stream.get();

    while (true) {
      if (!std::holds_alternative<char>(token)) {
        stream.putback(token);
        return x;
      }

      switch (std::get<char>(token)) {
      case '*':
        x *= factor(stream);
        break;
      case '/':
        x /= factor(stream);
        break;
      case '%': {
        double y = factor(stream);
        x = std::fmod(x, y);
        break;
      }
      default:
        stream.putback(token);
        return x;
      }

      token = stream.get();
    }
  }

  double factor(Stream &stream) {
    double x = primary(stream);
    auto token = stream.get();

    while (true) {
      if (std::holds_alternative<char>(token) && std::get<char>(token) == '!') {
        x = factorial(x);
        token = stream.get();
      } else {
        stream.putback(token);
        return x;
      }
    }
  }

  double primary(Stream &stream) {
    auto token = stream.get();

    if (std::holds_alternative<char>(token)) {
      char ch = std::get<char>(token);
      if (ch == '+' || ch == '-') {
        double val = primary(stream);
        return (ch == '+') ? val : -val;
      }

      if (ch == '(' || ch == '[' || ch == '{') {
        double x = expression(stream);
        char close = std::get<char>(stream.get());
        if (!matching_brackets(ch, close))
          throw std::runtime_error("Mismatched brackets");
        return x;
      }
    }

    if (std::holds_alternative<double>(token))
      return std::get<double>(token);

    if (std::holds_alternative<std::string>(token)) {
      auto name = std::get<std::string>(token);
      return m_variables.at(name);
    }

    throw std::runtime_error("Invalid token in primary");
  }

  bool matching_brackets(char open, char close) const {
    return (open == '(' && close == ')') || (open == '[' && close == ']') ||
           (open == '{' && close == '}');
  }

  double factorial(double x) const {
    if (x < 0 || std::floor(x) != x)
      throw std::runtime_error("Factorial of negative or non-integer");
    double result = 1;
    for (int i = 2; i <= static_cast<int>(x); ++i)
      result *= i;
    return result;
  }

  std::unordered_map<std::string, double> m_variables;
};

int main() {
  Calculator().test();
}
