#include <iostream>
#include <memory>

struct Data {
    int a;
    double b;
    std::string text;
};

struct Container {
    std::shared_ptr<Data> data;

    explicit Container(int x, double y, std::string z)
        : data(std::make_shared<Data>(Data{x, y, std::move(z)})) {}

    std::shared_ptr<int> getA() { return std::shared_ptr<int>(data, &data->a); }
    std::shared_ptr<double> getB() { return std::shared_ptr<double>(data, &data->b); }
    std::shared_ptr<std::string> getText() { return std::shared_ptr<std::string>(data, &data->text); }
};

int main() {
    Container c(42, 3.14, "Пример");

    std::shared_ptr<int> pA = c.getA();
    std::shared_ptr<double> pB = c.getB();
    std::shared_ptr<std::string> pText = c.getText();

    std::cout << "a: " << *pA << "\n";
    std::cout << "b: " << *pB << "\n";
    std::cout << "text: " << *pText << "\n";

    return 0;
}
