#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>
#include <iterator>

int main() {
    using namespace std;
    using namespace std::ranges;

    // std::ranges::count
    vector<int> v = {1, 2, 3, 4, 2, 5, 1};
    int count_result = count(v, 2);
    cout << "1. Количество двоек: " << count_result << "\n";

    // std::ranges::mismatch
    vector<int> v1 = {1, 2, 3, 4, 5};
    vector<int> v2 = {1, 2, 10, 4, 5};
    auto [mismatch_first, mismatch_second] = mismatch(v1, v2);
    if (mismatch_first != v1.end())
        cout << "2. Первое несовпадение: " << *mismatch_first << " и " << *mismatch_second << "\n";

    // std::ranges::equal
    bool are_equal = equal(v1, v2);
    cout << "3. Векторы равны: " << boolalpha << are_equal << "\n";

    // std::ranges::search
    vector<int> pattern = {3, 4};
    auto search_result = search(v1, pattern);
    if (!search_result.empty())
        cout << "4. Шаблон найден, начиная с: " << distance(v1.begin(), search_result.begin()) << "\n";

    // std::ranges::replace
    replace(v, 2, 9);
    cout << "5. После замены: ";
    for (int n : v) cout << n << " ";
    cout << "\n";

    // std::ranges::remove
    v.erase(remove(v, 9), v.end());
    cout << "6. После удаления 9: ";
    for (int n : v) cout << n << " ";
    cout << "\n";

    // std::ranges::unique
    vector<int> unique_vec = {1, 1, 2, 2, 3, 3, 4};
    unique_vec.erase(unique(unique_vec), unique_vec.end());
    cout << "7. После unique: ";
    for (int n : unique_vec) cout << n << " ";
    cout << "\n";

    // std::ranges::rotate
    vector<int> rot_vec = {1, 2, 3, 4, 5};
    rotate(rot_vec, rot_vec.begin() + 2);
    cout << "8. После rotate: ";
    for (int n : rot_vec) cout << n << " ";
    cout << "\n";

    // std::ranges::partition
    vector<int> part_vec = {1, 2, 3, 4, 5, 6, 7};
    partition(part_vec, [](int n) { return n % 2 == 0; });
    cout << "9. После partition: ";
    for (int n : part_vec) cout << n << " ";
    cout << "\n";

    // std::ranges::nth_element
    vector<int> nth_vec = {7, 1, 4, 3, 8, 5, 2, 6};
    nth_element(nth_vec, nth_vec.begin() + 3);
    cout << "10. После nth_element (3-й наименьший элемент в правильной позиции): ";
    for (int n : nth_vec) cout << n << " ";
    cout << "\n";

    return 0;
}
