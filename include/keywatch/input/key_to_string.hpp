#pragma once

#include <string>

namespace keywatch::input {

// Translate a Windows virtual-key code into the character(s) it produces,
// honouring the current Shift / Caps Lock state. Returns "" for keys that
// have no printable representation.
std::string key_to_string(int key);

} // namespace keywatch::input
