#include <iostream>
#include <vector>
#include <variant>
#include <optional>
#include <stdexcept>

void demonstrateBadAlloc() {
    try {
        std::vector<int> v;
        while (true) {
            v.push_back(1);
        }
    } catch (const std::bad_alloc& e) {
        std::cerr << "Caught std::bad_alloc: " << e.what() << std::endl;
    }
}

void demonstrateBadVariantAccess() {
    try {
        std::variant<int, std::string> var = 42;
        std::cout << std::get<std::string>(var) << std::endl;
    } catch (const std::bad_variant_access& e) {
        std::cerr << "std::bad_variant_access: " << e.what() << std::endl;
    }
}

void demonstrateBadOptionalAccess() {
    try {
        std::optional<int> opt;
        std::cout << opt.value() << std::endl;
    } catch (const std::bad_optional_access& e) {
        std::cerr << "std::bad_optional_access: " << e.what() << std::endl;
    }
}

void demonstrateLengthError() {
    try {
        std::vector<int> v;
        v.reserve(SIZE_MAX);
    } catch (const std::length_error& e) {
        std::cerr << "Caught std::length_error: " << e.what() << std::endl;
    }
}

void demonstrateOutOfRange() {
    try {
        std::vector<int> v = {1, 2, 3};
        std::cout << v.at(10) << std::endl;
    } catch (const std::out_of_range& e) {
        std::cerr << "Caught std::out_of_range: " << e.what() << std::endl;
    }
}

int main() {
    std::cout << "Demonstrating exceptions in C++ STL:" << std::endl;

    std::cout << "\n1. std::bad_alloc:" << std::endl;
    demonstrateBadAlloc();

    std::cout << "\n2. std::bad_variant_access:" << std::endl;
    demonstrateBadVariantAccess();

    std::cout << "\n3. std::bad_optional_access:" << std::endl;
    demonstrateBadOptionalAccess();

    std::cout << "\n4. std::length_error:" << std::endl;
    demonstrateLengthError();

    std::cout << "\n5. std::out_of_range:" << std::endl;
    demonstrateOutOfRange();

    return 0;
}
