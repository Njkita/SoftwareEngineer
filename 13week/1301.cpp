#include <cstdint>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::string bytesToHexString(const std::vector<uint8_t>& data) {
    std::ostringstream out;
    out << std::hex << std::uppercase;

    for (auto byte : data) {
        out << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
    }

    return out.str();
}

int main() {
    std::vector<uint8_t> example = {0xBA, 0xAD, 0xF0, 0x0D};

    std::string hex = bytesToHexString(example);
    std::cout << hex << '\n';

    return 0;
}
