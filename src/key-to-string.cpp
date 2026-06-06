#include <windows.h>

#include "key-to-string.hpp"

string key_to_string(int key) {
  if (key >= 'A' && key <= 'Z') {
    return string(1, char(key));
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
