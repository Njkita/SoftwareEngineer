#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

bool is_blank_line(const std::string &line) {
  for (char c : line) {
    if (!std::isspace(static_cast<unsigned char>(c))) {
      return false;
    }
  }
  return true;
}

int main() {
  std::string filename;
  std::cout << "Enter filename: ";
  std::getline(std::cin, filename);

  std::ifstream in_file(filename);
  if (!in_file) {
    std::cerr << "Error: Could not open file.\n";
    return 1;
  }

  std::vector<std::string> filtered_lines;
  std::string line;
  while (std::getline(in_file, line)) {
    if (!is_blank_line(line)) {
      filtered_lines.push_back(line);
    }
  }
  in_file.close();

  std::ofstream out_file(filename);
  if (!out_file) {
    std::cerr << "Error: Could not write to file.\n";
    return 1;
  }

  for (const auto &s : filtered_lines) {
    out_file << s << '\n';
  }
  out_file.close();

  std::cout << "Done. Blank lines removed.\n";
  return 0;
}