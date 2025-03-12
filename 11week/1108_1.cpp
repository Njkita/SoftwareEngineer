#include <cmath>
#include <iostream>
#include <utility>
#include <variant>

using Solution = std::variant<std::monostate, double, std::pair<double, double>>;

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

struct SolutionPrinter {
    void operator()(const std::monostate&) const {
        std::cout << "0 solutions" << std::endl;
    }

    void operator()(double root) const {
        std::cout << "1 solution: " << root << std::endl;
    }

    void operator()(const std::pair<double, double>& roots) const {
        std::cout << "2 solutions: " << roots.first << " , " << roots.second << std::endl;
    }
};

int main() {
    double a, b, c;
    std::cout << "a, b, c: ";
    std::cin >> a >> b >> c;

    Solution solution = Solve(a, b, c);
    std::visit(SolutionPrinter{}, solution);

    return 0;
}