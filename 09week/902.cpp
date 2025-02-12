#include <iostream>
#include <source_location>
#include <string>

class Logger {
public:
  Logger(const std::string &function_name,
         const std::source_location &location = std::source_location::current())
      : function_name_(function_name), location_(location) {
    logMessage("Entering");
  }

  ~Logger() {
    logMessage("Exiting");
  }

  static void
  log(const std::string &message, const std::string &function_name = "",
      const std::source_location &location = std::source_location::current()) {
    std::cout << message << " function: " << function_name << " at "
              << location.file_name() << ":" << location.line() << " ("
              << location.column() << ")\n";
  }

private:
  void logMessage(const std::string &message) const {
    Logger::log(message, function_name_,
                location_);
  }

  std::string function_name_;
  std::source_location location_;
};

void exampleFunction() {
  Logger logger(__FUNCTION__);
}

int main() {
  exampleFunction();
  return 0;
}
