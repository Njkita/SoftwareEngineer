#include <cmath>
#include <iostream>
#include <utility>
#include <variant>

using Solution =
    std::variant<std::monostate, double, std::pair<double, double>>;

Solution Solve(double a, double b, double c) {

  double D = b * b - 4 * a * c;

  if (D > 0.0) {
    double x1 = (-b + std::sqrt(D)) / (2 * a);
    double x2 = (-b - std::sqrt(D)) / (2 * a);
    return std::make_pair(x1, x2);
  } else if (D == 0.0) {
    double root = -b / (2 * a);
    return root;
  } else {
    return std::monostate{};
  }
}

void printSolution(const Solution &solution) {
  if (std::holds_alternative<std::monostate>(solution)) {
    std::cout << "0 solutions" << std::endl;
  } else if (std::holds_alternative<double>(solution)) {
    std::cout << "1 solution: " << std::get<double>(solution) << std::endl;
  } else if (std::holds_alternative<std::pair<double, double>>(solution)) {
    auto roots = std::get<std::pair<double, double>>(solution);
    std::cout << "2 solutions: " << roots.first << " , " << roots.second
              << std::endl;
  }
}

int main() {

  double a, b, c;
  std::cout << "a, b, c: ";
  std::cin >> a >> b >> c;

  Solution solution = Solve(a, b, c);
  printSolution(solution);

  return 0;
}
