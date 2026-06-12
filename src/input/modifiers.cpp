#include "keywatch/input/modifiers.hpp"

#include <windows.h>

namespace keywatch::input {

bool shift_down() { return (GetKeyState(VK_SHIFT) & 0x8000) != 0; }

bool capslock_on() { return (GetKeyState(VK_CAPITAL) & 0x0001) != 0; }

} // namespace keywatch::input
