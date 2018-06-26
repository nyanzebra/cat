#pragma once

#include "deps/std.hpp"

namespace syntax {

enum class ordering : unsigned char { kLEFT_TO_RIGHT, kRIGHT_TO_LEFT };

struct precedence { size_t _priority; ordering _ordering; };
/*
type()   type{}	Functional cast | 13
a()	Function call               | 14
a[]	Subscript                   | 15
(type)  CStyle cast             | 26
*/
static const std::unordered_map<std::string, precedence> gUNARY_OPERATORS = {
  { "+", { 0x22, ordering::kRIGHT_TO_LEFT } }, // +a
  { "++", { 0x20, ordering::kRIGHT_TO_LEFT } }, // ++a prefix
  { "++", { 0x10, ordering::kLEFT_TO_RIGHT } }, // a++ postfix
  { "-", { 0x23, ordering::kRIGHT_TO_LEFT } }, // -a
  { "--", { 0x21, ordering::kRIGHT_TO_LEFT } }, // --a prefix
  { "--", { 0x11, ordering::kLEFT_TO_RIGHT } }, // a-- postfix
  { "*", { 0x0, ordering::kRIGHT_TO_LEFT } }, // *a
  { "&", { 0x0, ordering::kRIGHT_TO_LEFT } }, // &a
  // logical
  { "!", { 0x0, ordering::kRIGHT_TO_LEFT } }, // !a
  // binary
  { "~", { 0x0, ordering::kRIGHT_TO_LEFT } }, // ~a
  // memory
  { "new", { 0x2A, ordering::kRIGHT_TO_LEFT } },
  { "delete", { 0x2C, ordering::kRIGHT_TO_LEFT } },
  { "new[]", { 0x2B, ordering::kRIGHT_TO_LEFT } },
  { "delete[]", { 0x2D, ordering::kRIGHT_TO_LEFT } },
  // other
  { "sizeof", { 0x29, ordering::kRIGHT_TO_LEFT } },
  { "throw", { 0x152, ordering::kRIGHT_TO_LEFT } },
};

static const std::unordered_map<std::string, precedence> gBINARY_OPERATORS = {
  // class scope, is only used for getting member pointers
  { "::", { 0x0, ordering::kLEFT_TO_RIGHT } },
  // access
  { "[]", { 0x10, ordering::kLEFT_TO_RIGHT } },
  { "()", { 0x10, ordering::kLEFT_TO_RIGHT } },
  // arithmetic
  { "+", { 0x50, ordering::kLEFT_TO_RIGHT } },
  { "-", { 0x51, ordering::kLEFT_TO_RIGHT } },
  { "/", { 0x41, ordering::kLEFT_TO_RIGHT } },
  { "*", { 0x40, ordering::kLEFT_TO_RIGHT } },
  { "**", { 0x10, ordering::kLEFT_TO_RIGHT } },
  { "%", { 0x42, ordering::kLEFT_TO_RIGHT } },
  // binary
  { "^", { 0x110, ordering::kLEFT_TO_RIGHT } },
  { "&", { 0x100, ordering::kLEFT_TO_RIGHT } },
  { "|", { 0x120, ordering::kLEFT_TO_RIGHT } },
  { "<<", { 0x60, ordering::kLEFT_TO_RIGHT } },
  { ">>", { 0x61, ordering::kLEFT_TO_RIGHT } },
  // reference
  { ".", { 0x16, ordering::kLEFT_TO_RIGHT } },
  { "->", { 0x17, ordering::kLEFT_TO_RIGHT } },
  { ".*", { 0x30, ordering::kLEFT_TO_RIGHT } },
  { "->*", { 0x30, ordering::kLEFT_TO_RIGHT } },
  // logical
  { "||", { 0x140, ordering::kLEFT_TO_RIGHT } },
  { "&&", { 0x130, ordering::kLEFT_TO_RIGHT } },
  // conditional
  { "<", { 0x80, ordering::kLEFT_TO_RIGHT } },
  { "<=", { 0x81, ordering::kLEFT_TO_RIGHT } },
  { ">", { 0x82, ordering::kLEFT_TO_RIGHT } },
  { ">=", { 0x83, ordering::kLEFT_TO_RIGHT } },
  { "<=>", { 0x70, ordering::kLEFT_TO_RIGHT } },
  { "==", { 0x90, ordering::kLEFT_TO_RIGHT } },
  { "!=", { 0x91, ordering::kLEFT_TO_RIGHT } },
  // assign
  { "=", { 0x153, ordering::kRIGHT_TO_LEFT } },
  { "+=", { 0x154, ordering::kRIGHT_TO_LEFT } },
  { "-=", { 0x155, ordering::kRIGHT_TO_LEFT } },
  { "*=", { 0x156, ordering::kRIGHT_TO_LEFT } },
  { "/=", { 0x157, ordering::kRIGHT_TO_LEFT } },
  { "%=", { 0x158, ordering::kRIGHT_TO_LEFT } },
  { "<<=", { 0x159, ordering::kRIGHT_TO_LEFT } },
  { ">>=", { 0x15A, ordering::kRIGHT_TO_LEFT } },
  { "&=", { 0x15B, ordering::kRIGHT_TO_LEFT } },
  { "^=", { 0x15C, ordering::kRIGHT_TO_LEFT } },
  { "|=", { 0x15D, ordering::kRIGHT_TO_LEFT } },
  // comma
  { ",", { 0x160, ordering::kLEFT_TO_RIGHT } },
  // ternary
  { "?", { 0x150, ordering::kLEFT_TO_RIGHT } },
  { ":", { 0x151, ordering::kLEFT_TO_RIGHT } }
};

} // namespace syntax
