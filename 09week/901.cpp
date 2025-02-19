#include <iostream>
#include <fstream>

class File {
    std::fstream file;
public:
    explicit File(const std::string& name) {
        file.open(name, std::ios::out);
        if (!file) {
            throw std::runtime_error("Ошибка открытия");
        }
    }

    void write(const std::string& text) {
        file << text << "\n";
    }

    ~File() {
        if (file.is_open()) {
            file.close();
            std::cout << "Файл закрыт\n";
        }
    }
};

int main() {
    try {
        File f("test.txt");
        f.write("Привет");
    } catch (const std::exception& e) {
        std::cout << "Ошибка: " << e.what() << "\n";
    }
    return 0;
}
