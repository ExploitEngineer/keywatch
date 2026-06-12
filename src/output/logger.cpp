#include "keywatch/output/logger.hpp"

#include <fstream>
#include <iostream>
#include <utility>

namespace keywatch::output {

Logger::Logger(std::string path) : path_(std::move(path)) {}

void Logger::write(const std::string &text) {
  std::ofstream data(path_, std::ios::trunc);

  if (data.is_open()) {
    data << text;
  } else {
    std::cerr << "Failed to open file: " << path_ << '\n';
  }
}

} // namespace keywatch::output
