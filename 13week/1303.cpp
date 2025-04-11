#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

struct Process {
  std::string name;
  int pid;
  std::string status;
  std::string user;
};

int main() {
  std::vector<Process> processes = {
    {"vscode",     2453, "running",   "nikita"},
    {"gmail",      3120, "sleeping",  "nikita"},
    {"discord",    3777, "running",   "nikita"},
    {"photoshop",  4812, "idle",      "nikita"},
    {"steam",      1938, "running",   "nikita"},
    {"spotify",    2201, "sleeping",  "nikita"},
};

  std::cout << std::left << std::setw(15) << "NAME" << std::setw(8) << "PID"
            << std::setw(12) << "STATUS" << std::setw(10) << "USER" << '\n';

  std::cout << std::string(45, '-') << '\n';

  for (const auto &proc : processes) {
    std::cout << std::setw(15) << proc.name << std::setw(8) << proc.pid
              << std::setw(12) << proc.status << std::setw(10) << proc.user
              << '\n';
  }

  return 0;
}
