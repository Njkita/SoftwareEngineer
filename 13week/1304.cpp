#include <iostream>

int main()
{
    std::cout << R"(')" << R"(")" << '\n';

    std::cout << R"(")" << R"(')" << "\n";

    std::cout << R"("// not comment")" << '\n';

    std::cout << R"(/* not comment */)" << '\n';

    return 0;
}
