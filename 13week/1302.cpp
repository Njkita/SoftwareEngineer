#include <iostream>
#include <iomanip>

int main() {
    const int N = 10;
    int row[N + 1] = {};

    row[0] = 1;

    for (int i = 0; i < N; ++i) {
        std::cout << std::setw((N - i) * 2);
        for (int j = 0; j <= i; ++j) {
            std::cout << row[j] << "   ";
        }
        std::cout << '\n';
        for (int j = i + 1; j > 0; --j) {
            row[j] += row[j - 1];
        }
    }

    return 0;
}
