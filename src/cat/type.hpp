#pragma once

#include "utility/enum.hpp"

namespace cat {

enum class type : unsigned long long {
  kNONE,
  kNULLPTR,
  kVOID,
  kBOOL,
  kCHAR,
  kBYTE,
  kINT8,
  kINT16,
  kINT32,
  kINT64,
  kUINT8,
  kUINT16,
  kUINT32,
  kUINT64,
  kFLT32,
  kFLT64,
  kPOINTER,
  kREFERENCE,
  kAUTO,
  kCLASS,
  kINTERFACE,
  kFUNCTION,
  kPATTERN
}; //enum type

} // namespace cat
