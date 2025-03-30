#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main() {
    // std::count
    std::vector<int> v = {1, 2, 3, 4, 2, 5, 1};
    int count = std::count(v.begin(), v.end(), 2);
    std::cout << "1. Количество двоек: " << count << "\n";

    // std::mismatch
    std::vector<int> v1 = {1, 2, 3, 4, 5};
    std::vector<int> v2 = {1, 2, 10, 4, 5};
    auto mismatch_result = std::mismatch(v1.begin(), v1.end(), v2.begin());
    if (mismatch_result.first != v1.end())
        std::cout << "2. Первое несовпадение: " << *mismatch_result.first << " и " << *mismatch_result.second << "\n";

    // std::equal
    bool are_equal = std::equal(v1.begin(), v1.end(), v2.begin());
    std::cout << "3. Векторы равны: " << std::boolalpha << are_equal << "\n";

    // std::search
    std::vector<int> pattern = {3, 4};
    auto search_result = std::search(v1.begin(), v1.end(), pattern.begin(), pattern.end());
    if (search_result != v1.end())
        std::cout << "4. Шаблон найден, начиная с: " << std::distance(v1.begin(), search_result) << "\n";

    // std::replace
    std::replace(v.begin(), v.end(), 2, 9);
    std::cout << "5. После замены: ";
    for (int n : v) std::cout << n << " ";
    std::cout << "\n";

    // std::remove
    auto remove_end = std::remove(v.begin(), v.end(), 9);
    v.erase(remove_end, v.end());
    std::cout << "6. После удаления 9: ";
    for (int n : v) std::cout << n << " ";
    std::cout << "\n";

    // std::unique
    std::vector<int> unique_vec = {1, 1, 2, 2, 3, 3, 4};
    auto unique_end = std::unique(unique_vec.begin(), unique_vec.end());
    unique_vec.erase(unique_end, unique_vec.end());
    std::cout << "7. После unique: ";
    for (int n : unique_vec) std::cout << n << " ";
    std::cout << "\n";

    // std::rotate
    std::vector<int> rot_vec = {1, 2, 3, 4, 5};
    std::rotate(rot_vec.begin(), rot_vec.begin() + 2, rot_vec.end());
    std::cout << "8. После rotate: ";
    for (int n : rot_vec) std::cout << n << " ";
    std::cout << "\n";

    // std::partition
    std::vector<int> part_vec = {1, 2, 3, 4, 5, 6, 7};
    std::partition(part_vec.begin(), part_vec.end(), [](int n) { return n % 2 == 0; });
    std::cout << "9. После partition: ";
    for (int n : part_vec) std::cout << n << " ";
    std::cout << "\n";

    // std::nth_element
    std::vector<int> nth_vec = {7, 1, 4, 3, 8, 5, 2, 6};
    std::nth_element(nth_vec.begin(), nth_vec.begin() + 3, nth_vec.end());
    std::cout << "10. После nth_element (3-й наименьший элемент в правильной позиции): ";
    for (int n : nth_vec) std::cout << n << " ";
    std::cout << "\n";

    return 0;
}
