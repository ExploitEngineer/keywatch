#include <windows.h>

#include "handle-capslock.hpp"
#include "handle-shift.hpp"
#include "key-to-string.hpp"

string key_to_string(int key) {
  if (key >= 'A' && key <= 'Z') {
    bool CapsLock = handle_CapsLock();
    bool Shift = handle_Shift();

    if (CapsLock ^ Shift) {
      return string(1, char(key));
    } else {
      return string(1, char(key + 32));
    }
  }

  switch (key) {
  case VK_RETURN:
    return "\n";
  case VK_SPACE:
    return " ";
  case VK_TAB:
    return "\t";
  default:
    return "";
  }
}
