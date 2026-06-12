#pragma once

#include <string>

namespace keywatch::output {

// Persists captured text to a file, rewriting the whole buffer on each call.
class Logger {
public:
  explicit Logger(std::string path = "data.txt");

  // Truncate the target file and write `text` in full.
  void write(const std::string &text);

private:
  std::string path_;
};

} // namespace keywatch::output
