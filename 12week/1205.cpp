#include <cctype>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

std::vector<uint8_t> hexStringToBytes(const std::string &hexStr) {
  if (hexStr.size() % 2 != 0) {
    throw std::invalid_argument(
        "Input string must have even number of characters");
  }

  std::vector<uint8_t> bytes;

  for (size_t i = 0; i < hexStr.size(); i += 2) {
    char highNibble = toupper(hexStr[i]);
    char lowNibble = toupper(hexStr[i + 1]);

    if (!isxdigit(highNibble) || !isxdigit(lowNibble)) {
      throw std::invalid_argument("Invalid hexadecimal digit");
    }

    uint8_t byte = 0;
    if (isdigit(highNibble)) {
      byte = (highNibble - '0') << 4;
    } else {
      byte = (highNibble - 'A' + 10) << 4;
    }
    if (isdigit(lowNibble)) {
      byte |= lowNibble - '0';
    } else {
      byte |= lowNibble - 'A' + 10;
    }

    bytes.push_back(byte);
  }

  return bytes;
}

int main() {
  std::string test = "BAAD";
  auto result = hexStringToBytes(test);

  for (size_t i = 0; i < result.size(); ++i) {
    std::cout << "0x" << std::hex << std::uppercase << std::setw(2)
              << std::setfill('0') << static_cast<int>(result[i]);
    if (i != result.size() - 1) {
      std::cout << ", ";
    }
  }
  std::cout << std::endl;

  return 0;
}