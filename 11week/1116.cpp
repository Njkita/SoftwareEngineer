#include <iostream>
#include <vector>
#include <ranges>
#include <string>
#include <sstream>
#include <iterator>

int main() {
    // 1. views::istream
    std::istringstream input("10 20 30 40 50");
    auto numbers = std::ranges::istream_view<int>(input);
    std::cout << "1. Чтение из потока: ";
    for (int n : numbers) std::cout << n << " ";
    std::cout << "\n";

    // 2. views::counted
    std::vector<int> v = {1, 2, 3, 4, 5};
    auto counted_view = std::views::counted(v.begin(), 3);
    std::cout << "2. Первые 3 элемента: ";
    for (int n : counted_view) std::cout << n << " ";
    std::cout << "\n";

    // 3. views::join
    std::vector<std::string> words = {"Hello", "World", "C++"};
    std::vector<std::vector<char>> char_vectors;
    for (const auto& word : words) char_vectors.push_back(std::vector<char>(word.begin(), word.end()));

    auto joined_chars = char_vectors | std::views::join;
    std::cout << "3. Объединенные символы: ";
    for (char ch : joined_chars) std::cout << ch;
    std::cout << "\n";

    // 4. views::stride
    auto stride_view = v | std::views::stride(2);
    std::cout << "4. Каждый второй элемент: ";
    for (int n : stride_view) std::cout << n << " ";
    std::cout << "\n";

    return 0;
}
