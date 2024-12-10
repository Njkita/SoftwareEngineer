#include <cassert>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

template <typename C> void print(const std::string &name) {
  std::cout << name << " : tick = ";

  std::cout << std::setprecision(9) << std::fixed
            << 1.0 * C::period::num / C::period::den;

  if (C::is_steady) {
    std::cout << " / steady";
  }

  std::cout << '\n';
}

class Chronometer {
public:
  using clock_t = std::chrono::steady_clock;

  Chronometer() : m_is_running(false) {}

  void start() {
    if (m_is_running) {
      throw std::runtime_error("Chronometer is already running");
    }
    m_start_time = clock_t::now();
    m_is_running = true;
  }

  void stop() {
    if (!m_is_running) {
      throw std::runtime_error("Chronometer is not running");
    }
    auto m_end_time = clock_t::now();
    auto interval =
        std::chrono::duration_cast<std::chrono::microseconds>(m_end_time - m_start_time);
    m_intervals.push_back(interval);
    m_is_running = false;
  }

  double average() const {
    if (m_intervals.empty()) {
      throw std::runtime_error("No intervals recorded");
    }
    auto total = std::chrono::microseconds(0);
    for (const auto &interval : m_intervals) {
      total += interval;
    }
    return static_cast<double>(total.count()) /
           (m_intervals.size() * 1'000'000.0);
  }

  void reset() {
    m_intervals.clear();
    m_is_running = false;
  }

private:
  bool m_is_running;
  clock_t::time_point m_start_time;
  std::vector<std::chrono::microseconds> m_intervals;
};

int main() {
  print<std::chrono::system_clock>("system");
  print<std::chrono::steady_clock>("steady");

  try {
    Chronometer chronometer;

    chronometer.start();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    chronometer.stop();

    chronometer.start();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    chronometer.stop();

    std::cout << "Average: " << std::setprecision(6) << std::fixed
              << chronometer.average() << " seconds\n";
    chronometer.reset();
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }

  return 0;
}
