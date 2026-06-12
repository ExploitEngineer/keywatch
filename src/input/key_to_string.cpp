#include "keywatch/input/key_to_string.hpp"

#include <windows.h>

#include "keywatch/input/modifiers.hpp"

namespace keywatch::input {

namespace {

// US-layout digit row: index 0..9 maps VK '0'..'9' to its shifted symbol.
constexpr char kDigitShift[10] = {')', '!', '@', '#', '$',
                                  '%', '^', '&', '*', '('};

// US-layout punctuation: virtual key -> {unshifted, shifted}.
struct OemKey {
  int vk;
  char base;
  char shifted;
};

constexpr OemKey kOemKeys[] = {
    {VK_OEM_1, ';', ':'},      {VK_OEM_PLUS, '=', '+'},
    {VK_OEM_COMMA, ',', '<'},  {VK_OEM_MINUS, '-', '_'},
    {VK_OEM_PERIOD, '.', '>'}, {VK_OEM_2, '/', '?'},
    {VK_OEM_3, '`', '~'},      {VK_OEM_4, '[', '{'},
    {VK_OEM_5, '\\', '|'},     {VK_OEM_6, ']', '}'},
    {VK_OEM_7, '\'', '"'},
};

} // namespace

std::string key_to_string(int key) {
  const bool shift = shift_down();

  // Letters: case decided by Caps Lock XOR Shift.
  if (key >= 'A' && key <= 'Z') {
    const bool upper = capslock_on() ^ shift;
    return std::string(1, char(upper ? key : key + 32));
  }

  // Digit row.
  if (key >= '0' && key <= '9') {
    return std::string(1, shift ? kDigitShift[key - '0'] : char(key));
  }

  // Punctuation keys.
  for (const OemKey &oem : kOemKeys) {
    if (key == oem.vk) {
      return std::string(1, shift ? oem.shifted : oem.base);
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

} // namespace keywatch::input
