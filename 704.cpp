#include <iostream>
#include <vector>
#include <variant>
#include <optional>
#include <stdexcept>

void BadAlloc() {
    try {
        std::vector<int> v;
        while (true) {
            v.push_back(1);
        }
    } catch (const std::bad_alloc& e) {
        std::cerr << "Caught std::bad_alloc: " << e.what() << std::endl;
    }
}

void BadVariantAccess() {
    try {
        std::variant<int, std::string> var = 42;
        std::cout << std::get<std::string>(var) << std::endl;
    } catch (const std::bad_variant_access& e) {
        std::cerr << "Caught std::bad_variant_access: " << e.what() << std::endl;
    }
}

void BadOptionalAccess() {
    try {
        std::optional<int> opt;
        std::cout << opt.value() << std::endl;
    } catch (const std::bad_optional_access& e) {
        std::cerr << "Caught std::bad_optional_access: " << e.what() << std::endl;
    }
}

void LengthError() {
    try {
        std::vector<int> v;
        v.reserve(SIZE_MAX);
    } catch (const std::length_error& e) {
        std::cerr << "Caught std::length_error: " << e.what() << std::endl;
    }
}

void OutOfRange() {
    try {
        std::vector<int> v = {1, 2, 3};
        std::cout << v.at(10) << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Caught std::out_of_range: " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "std::bad_alloc:" << std::endl;
    BadAlloc();

    std::cout << "\n std::bad_variant_access:" << std::endl;
    BadVariantAccess();

    std::cout << "\n std::bad_optional_access:" << std::endl;
    BadOptionalAccess();

    std::cout << "\n std::length_error:" << std::endl;
    LengthError();

    std::cout << "\n std::out_of_range:" << std::endl;
    OutOfRange();

    return 0;
}
