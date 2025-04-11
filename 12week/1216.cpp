#include <iostream>
#include <regex>
#include <string>
#include <tuple>

std::tuple<std::string, std::string, std::string, std::string>
extract_url_parts(const std::string &raw) {
  static const std::regex url_re(
      R"(^([a-zA-Z][a-zA-Z0-9+\-.]*):\/\/([^\/:]+)(?::(\d+))?(\/[^?#]*)?)",
      std::regex::ECMAScript);

  std::smatch capture;
  if (!std::regex_search(raw, capture, url_re)) {
    throw std::invalid_argument("URL does not match expected pattern");
  }

  auto proto = capture[1].matched ? capture[1].str() : "";
  auto host = capture[2].matched ? capture[2].str() : "";
  auto port = capture[3].matched ? capture[3].str() : "default";
  auto path = capture[4].matched ? capture[4].str() : "/";

  return {proto, host, port, path};
}

int main() {
  std::string line;
  std::cout << "Enter URL (example: https://example.com:443/some/path):\n";
  std::getline(std::cin, line);

  try {
    auto [scheme, domain, port, route] = extract_url_parts(line);
    std::cout << "Protocol: " << scheme << "\n"
              << "Domain:   " << domain << "\n"
              << "Port:     " << port << "\n"
              << "Path:     " << route << "\n";
  } catch (const std::exception &e) {
    std::cerr << "Parsing error: " << e.what() << '\n';
  }

  return 0;
}

// https://contest.yandex.ru/contest/75228/problems/