#include "logger.hpp"
#include <iostream>
#include <windows.h>

using namespace std;

int main() {
  while (true) {
    // every key on the keyboard has a number called index
    // 65 = A
    for (int key = 8; key <= 190; key++) {
      if (GetAsyncKeyState(key) & 0x0001) {
        cout << "Key pressed: " << key;
      }
    }
  }
  return 0;
}
