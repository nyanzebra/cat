#pragma once

#include "std.hpp"

#include "token_type.hpp"

namespace syntax {

static const std::unordered_map<std::string, token_type> gKEYWORDS = {
  // types
  { "void", token_type::kTYPE },
  { "bool", token_type::kTYPE },
  { "char", token_type::kTYPE },
  { "byte", token_type::kTYPE },
  { "int8", token_type::kTYPE },
  { "int16", token_type::kTYPE },
  { "int32", token_type::kTYPE },
  { "int64", token_type::kTYPE },
  { "uint8", token_type::kTYPE },
  { "uint16", token_type::kTYPE },
  { "uint32", token_type::kTYPE },
  { "uint64", token_type::kTYPE },
  { "flt32", token_type::kTYPE },
  { "flt64", token_type::kTYPE },
  // modifiers
  { "volatile", token_type::kTYPE_MODIFIER },
  { "mutable", token_type::kTYPE_MODIFIER },
  { "static", token_type::kTYPE_MODIFIER },
  { "extern", token_type::kTYPE_MODIFIER }, // maybe need to rethink this... might need to be compile info
  // scope
  { "module", token_type::kMODULE },
  { "import", token_type::kIMPORT },
  { "public", token_type::kPUBLIC },
  { "protected", token_type::kPROTECTED },
  { "private", token_type::kPRIVATE },
  // conditions
  { "do", token_type::kDO },
  { "while", token_type::kWHILE },
  { "for", token_type::kFOR },
  { "if", token_type::kIF },
  { "else", token_type::kELSE },
  { "match", token_type::kMATCH },
  // asm
  { "asm", token_type::kASM },
  // meta
  { "class", token_type::kCLASS },
  { "interface", token_type::kINTERFACE },
  { "union", token_type::kUNION },
  { "enum", token_type::kENUM },
  { "this", token_type::kTHIS },
  // meta-util
  { "defines", token_type::kDEFINE }, // used when taking interface(s)
  { "using", token_type::kUSING }, // used when defining template entity using Policy... or using this = that<T>
  // cast
  { "as", token_type::kAS },
  // logical
  { "not", token_type::kNOT },
  { "or", token_type::kOR },
  { "and", token_type::kAND },
  // template
  { "template", token_type::kTEMPLATE }, // can be used with sizeof and [], [0] returns first 'type'
  { "typename", token_type::kTYPENAME },
  // except
  { "throw", token_type::kTHROW },
  //range
  { "..", token_type::kRANGE },
  // other
  { "...", token_type::kELLIPSIS },
  { "alignas", token_type::kALIGNAS },
  { "alignof", token_type::kALIGNOF },
  { "sizeof", token_type::kSIZEOF }, // can be use on type for size of type or template for number of args in parameter pack
  { "auto", token_type::kAUTO },
  { "nullptr", token_type::kNULLPTR },
  { "typedef", token_type::kTYPEDEF },
  { "operator", token_type::kOPERATOR },
  { "return", token_type::kRETURN },
  { "yield", token_type::kYIELD },
  { "unsafe", token_type::kUNSAFE }
};

} // namespace syntax
