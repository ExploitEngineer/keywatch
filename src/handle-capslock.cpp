#include <windows.h>

#include "handle-capslock.hpp"

bool handle_CapsLock() { return (GetKeyState(VK_CAPITAL) & 0x0001) != 0; }
