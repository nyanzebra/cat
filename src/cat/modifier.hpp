#pragma once

#include "utility/enum.hpp"

namespace cat {

enum class modifier : unsigned char {
  kNONE     = 0x0,
  kMUTABLE  = 0x1,
  kVOLATILE = 0x2,
  kSTATIC   = 0x4,
  kEXTERN   = 0x8
}; // enum modifier

} // namespace cat
