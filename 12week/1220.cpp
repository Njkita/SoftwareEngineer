#include <cctype>
#include <cmath>
#include <cstring>
#include <iostream>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>


enum class TokenType { Number, Operator, LeftBracket, RightBracket };
enum class Operator {
  Add,
  Subtract,
  Multiply,
  Divide,
  Modulo,
  Factorial,
  None
};

struct Token {
  TokenType type;
  double value;
  Operator op;
  char bracket;

  static Token make_number(double val) {
    return Token{TokenType::Number, val, Operator::None, 0};
  }

  static Token make_operator(Operator o) {
    return Token{TokenType::Operator, 0, o, 0};
  }

  static Token make_bracket(TokenType t, char b) {
    return Token{t, 0, Operator::None, b};
  }
};

int precedence(Operator op) {
  switch (op) {
  case Operator::Factorial:
    return 4;
  case Operator::Multiply:
  case Operator::Divide:
  case Operator::Modulo:
    return 3;
  case Operator::Add:
  case Operator::Subtract:
    return 2;
  default:
    return -1;
  }
}

bool is_right_associative(Operator op) { return op == Operator::Factorial; }

Operator char_to_operator(char c) {
  switch (c) {
  case '+':
    return Operator::Add;
  case '-':
    return Operator::Subtract;
  case '*':
    return Operator::Multiply;
  case '/':
    return Operator::Divide;
  case '%':
    return Operator::Modulo;
  case '!':
    return Operator::Factorial;
  default:
    return Operator::None;
  }
}

std::vector<Token> tokenize(const std::string &input) {
  std::vector<Token> tokens;
  std::istringstream stream(input);
  char ch;

  while (stream >> ch) {
    if (std::isdigit(ch) || ch == '.') {
      stream.putback(ch);
      double val;
      stream >> val;
      tokens.push_back(Token::make_number(val));
    } else if (strchr("+-*/%!()", ch)) {
      if (std::strchr("([{", ch))
        tokens.push_back(Token::make_bracket(TokenType::LeftBracket, ch));
      else if (std::strchr(")]}", ch))
        tokens.push_back(Token::make_bracket(TokenType::RightBracket, ch));
      else
        tokens.push_back(Token::make_operator(char_to_operator(ch)));
    } else {
      throw std::runtime_error(std::string("Invalid character: ") + ch);
    }
  }

  return tokens;
}

bool brackets_match(char open, char close) {
  return (open == '(' && close == ')') || (open == '[' && close == ']') ||
         (open == '{' && close == '}');
}

std::vector<Token> to_rpn(const std::vector<Token> &tokens) {
  std::vector<Token> output;
  std::stack<Token> ops;

  for (const auto &tok : tokens) {
    if (tok.type == TokenType::Number) {
      output.push_back(tok);
    } else if (tok.type == TokenType::Operator) {
      while (!ops.empty() && ops.top().type == TokenType::Operator) {
        auto top_op = ops.top().op;
        if ((precedence(tok.op) < precedence(top_op)) ||
            (precedence(tok.op) == precedence(top_op) &&
             !is_right_associative(tok.op))) {
          output.push_back(ops.top());
          ops.pop();
        } else {
          break;
        }
      }
      ops.push(tok);
    } else if (tok.type == TokenType::LeftBracket) {
      ops.push(tok);
    } else if (tok.type == TokenType::RightBracket) {
      while (!ops.empty() && ops.top().type != TokenType::LeftBracket) {
        output.push_back(ops.top());
        ops.pop();
      }
      if (ops.empty() || !brackets_match(ops.top().bracket, tok.bracket))
        throw std::runtime_error("Mismatched brackets");
      ops.pop();
    }
  }

  while (!ops.empty()) {
    if (ops.top().type == TokenType::LeftBracket)
      throw std::runtime_error("Unmatched opening bracket");
    output.push_back(ops.top());
    ops.pop();
  }

  return output;
}

double factorial(double val) {
  if (val < 0 || std::floor(val) != val)
    throw std::runtime_error("Invalid factorial operand");
  return std::tgamma(val + 1);
}

double apply_binary_op(Operator op, double a, double b) {
  switch (op) {
  case Operator::Add:
    return a + b;
  case Operator::Subtract:
    return a - b;
  case Operator::Multiply:
    return a * b;
  case Operator::Divide:
    return a / b;
  case Operator::Modulo:
    return std::fmod(a, b);
  default:
    throw std::runtime_error("Unknown binary operator");
  }
}

double evaluate_rpn(const std::vector<Token> &rpn) {
  std::stack<double> values;

  for (const auto &tok : rpn) {
    if (tok.type == TokenType::Number) {
      values.push(tok.value);
    } else if (tok.type == TokenType::Operator) {
      if (tok.op == Operator::Factorial) {
        if (values.empty())
          throw std::runtime_error("Missing operand for factorial");
        double v = values.top();
        values.pop();
        values.push(factorial(v));
      } else {
        if (values.size() < 2)
          throw std::runtime_error("Missing operands");
        double b = values.top();
        values.pop();
        double a = values.top();
        values.pop();
        values.push(apply_binary_op(tok.op, a, b));
      }
    }
  }

  if (values.size() != 1)
    throw std::runtime_error("Invalid expression");
  return values.top();
}

int main() {
  std::string line;

  std::cout << "Введите выражение (или 'q' для выхода):\n";
  while (std::getline(std::cin, line)) {
    if (line == "q")
      break;

    try {
      auto tokens = tokenize(line);
      auto rpn = to_rpn(tokens);
      double result = evaluate_rpn(rpn);
      std::cout << "Результат: " << result << '\n';
    } catch (const std::exception &e) {
      std::cout << "Ошибка: " << e.what() << '\n';
    }
  }

  return 0;
}
