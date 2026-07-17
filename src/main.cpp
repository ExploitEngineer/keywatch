#include "keywatch/app/keylogger.hpp"
#include <csignal>
#include <iostream>
#include <memory>

std::unique_ptr<keywatch::app::Keylogger> g_keylogger;

void signal_handler(int signal) {
  if (signal == SIGINT || signal == SIGTERM) {
    std::cout << "\nShutting down keylogger..." << std::endl;
    if (g_keylogger) {
      g_keylogger->stop();
    }
    exit(0);
  }
}

int main(int argc, char *argv[]) {
  std::string log_path = "data.txt";

  // Allow custom log path via command line
  if (argc > 1) {
    log_path = argv[1];
  }

  std::cout << "Keylogger started. Logging to: " << log_path << std::endl;
  std::cout << "Press Ctrl+Esc to exit." << std::endl;

  // Setup signal handling for graceful shutdown
  signal(SIGINT, signal_handler);
  signal(SIGTERM, signal_handler);

  try {
    g_keylogger = std::make_unique<keywatch::app::Keylogger>(log_path);
    g_keylogger->run();
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
