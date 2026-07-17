#include "keywatch/output/logger.hpp"

#include <chrono>
#include <fstream>
#include <iostream>
#include <utility>

namespace keywatch::output {

Logger::Logger(std::string path) : path_(std::move(path)) {}

void Logger::write(const std::string &text) {
  // Open in append mode to preserve history
  std::ofstream data(path_, std::ios::app);

  if (data.is_open()) {
    data << text << std::flush; // Flush immediately for real-time logging
  } else {
    // Try to create the file if it doesn't exist
    data.open(path_, std::ios::out);
    if (data.is_open()) {
      data << text << std::flush;
    } else {
      std::cerr << "Failed to open/create file: " << path_ << '\n';
    }
  }
}

} // namespace keywatch::output
