#pragma once

namespace syntax {

enum class modifiers : char {
  kNONE = 0x0,
  kMUTABLE = 0x1,
  kEXTERN = 0x2,
  kSTATIC = 0x4,
  kVOLATILE = 0x8
}; // enum modifiers

} // namespace syntax
