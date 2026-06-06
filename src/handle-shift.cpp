#include <windows.h>

#include <handle-shift.hpp>

bool handle_Shift() { return (GetKeyState(VK_CAPITAL) & 0x8000) != 0; }
