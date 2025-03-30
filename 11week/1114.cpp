#include <iostream>
#include <vector>
#include <numeric>
#include <iterator>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};

    // std::accumulate
    int sum = std::accumulate(v.begin(), v.end(), 0);
    std::cout << "1. Сумма элементов: " << sum << "\n";

    // std::inner_product
    std::vector<int> v2 = {5, 4, 3, 2, 1};
    int dot_product = std::inner_product(v.begin(), v.end(), v2.begin(), 0);
    std::cout << "2. Скалярное произведение: " << dot_product << "\n";

    // std::partial_sum
    std::vector<int> prefix_sums(v.size());
    std::partial_sum(v.begin(), v.end(), prefix_sums.begin());
    std::cout << "3. Префиксные суммы: ";
    std::copy(prefix_sums.begin(), prefix_sums.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";

    // std::adjacent_difference
    std::vector<int> adj_diff(v.size());
    std::adjacent_difference(v.begin(), v.end(), adj_diff.begin());
    std::cout << "4. Разности между соседними элементами: ";
    std::copy(adj_diff.begin(), adj_diff.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";

    return 0;
}
