#include <cmath>
#include <exception>
#include <iostream>
#include <istream>
#include <iterator>
#include <stdexcept>
#include <string_view>
#include <vector>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>

class Operand : public boost::spirit::x3::variant<
                    double, boost::spirit::x3::forward_ast<struct Sign>,

                    boost::spirit::x3::forward_ast<struct List>> {
public:
  using base_type::base_type;
  using base_type::operator=;
};

struct Sign {
  std::vector<char> prefix_ops;
  Operand operand;
  bool factorial = false;
};

struct Step {
  char operation = '\0';
  Operand operand;
};

struct List {
  Operand head;
  std::vector<Step> steps;
};

BOOST_FUSION_ADAPT_STRUCT(Sign, prefix_ops, operand, factorial)
BOOST_FUSION_ADAPT_STRUCT(Step, operation, operand)
BOOST_FUSION_ADAPT_STRUCT(List, head, steps)

namespace parser {
namespace x3 = boost::spirit::x3;

x3::rule<struct rule_1_tag, List> rule_1 = "rule_1";
x3::rule<struct rule_2_tag, List> rule_2 = "rule_2";
x3::rule<struct rule_3_tag, Operand> rule_3 = "rule_3";
x3::rule<struct operand_tag, Operand> operand = "operand";
x3::rule<struct sign_tag, Sign> sign = "sign";

auto const sign_def =
    x3::repeat(0, x3::inf)[x3::char_("+-")] >>
    (x3::double_ | ('(' >> rule_1 >> ')') | ('[' >> rule_1 >> ']') |
     ('{' >> rule_1 >> '}')) >>
    x3::attr(false) >>
    -(x3::char_('!')[([](auto &ctx) { x3::_val(ctx).factorial = true; })]);

auto const operand_def = sign;

auto const rule_3_def = operand;
auto const rule_2_def = rule_3 >> *(x3::char_("*/%") >> rule_3);
auto const rule_1_def = rule_2 >> *(x3::char_("+-") >> rule_2);

BOOST_SPIRIT_DEFINE(rule_1, rule_2, rule_3, operand, sign)
}

class Calculator {
public:
  auto operator()(double x) const -> double { return x; }

  auto operator()(const Sign &sign) const -> double {
    auto x = boost::apply_visitor(*this, sign.operand);

    for (auto it = sign.prefix_ops.rbegin(); it != sign.prefix_ops.rend();
         ++it) {
      switch (*it) {
      case '+':
        break;
      case '-':
        x *= -1;
        break;
      default:
        throw std::runtime_error("Unknown unary operator");
      }
    }

    if (sign.factorial) {
      if (x < 0 || std::floor(x) != x)
        throw std::runtime_error("Invalid factorial operand");
      x = std::tgamma(x + 1);
    }

    return x;
  }

  auto operator()(const Step &step, double x) const -> double {
    auto y = boost::apply_visitor(*this, step.operand);

    switch (step.operation) {
    case '+':
      return x + y;
    case '-':
      return x - y;
    case '*':
      return x * y;
    case '/':
      return x / y;
    case '%':
      return std::fmod(x, y);
    default:
      throw std::runtime_error("Unknown binary operator");
    }
  }

  auto operator()(const List &list) const -> double {
    auto x = boost::apply_visitor(*this, list.head);

    for (const auto &step : list.steps) {
      x = (*this)(step, x);
    }

    return x;
  }
};

auto parse(std::string_view view) {
  auto begin = std::begin(view), end = std::end(view);

  auto space = boost::spirit::x3::ascii::space;

  List list;

  bool success =
      boost::spirit::x3::phrase_parse(begin, end, parser::rule_1, space, list);

  if (!success || begin != end) {
    throw std::runtime_error("Parse error");
  }

  static Calculator calculator;

  return calculator(list);
}

int main() {
  std::string string;

  std::cout << "main : enter expression(s) (type ';' to quit): \n";

  while (std::getline(std::cin >> std::ws, string)) {
    if (!string.empty() && string.front() == ';')
      break;

    try {
      std::cout << "main : " << string << " = " << parse(string) << '\n';
    } catch (const std::exception &e) {
      std::cout << "main : error : " << e.what() << '\n';
    }
  }
}
