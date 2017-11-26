#pragma once

#include "std.hpp"

#include "utility/enum.hpp"

namespace syntax {

enum class token_type : unsigned long long {
  kPOSSIBLE_ENTITY,
  kERROR,
  // instances
  kNUMBER, // 1
  kCHAR_LITERAL, // 'a'
  kSTRING_LITERAL, // "a"
  // delimiter
  kOPENING_DELIMITER, // (, [, {
  kCLOSING_DELIMITER, // ), ], }
  kTERMINATOR, // ;
  kSEPARATOR, // ,
  // null
  kNULLPTR,
  // objects
  kDEFINE,
  kCLASS,
  kINTERFACE,
  kUNION,
  kENUM,
  kTHIS,
  // function
  kFUNCTION,
  kRETURN,
  kYIELD,
  // modules
  kMODULE,
  kIMPORT,
  // variables
  kVARIABLE,
  // types
  kAUTO,
  kTYPE,
  kTYPE_MODIFIER,
  kTEMPLATE,
  kTYPENAME,
  kAS,
  kUSING,
  kTYPEDEF,
  //flow
  kIF,
  kELSE,
  kMATCH,
  kFOR,
  kDO,
  kWHILE,
  // bool help
  kNOT,
  kOR,
  kAND,
  // scope
  kPUBLIC,
  kPROTECTED,
  kPRIVATE,
  // compile info
  kALIGNAS,
  kALIGNOF,
  kSIZEOF,
  kRANGE,
  kELLIPSIS,
  kEXTERN,
  kOPERATOR,
  // exception
  kTHROW,
  // asm
  kASM,
  // eof
  kEND_OF_FILE,
  kUNSAFE,
}; // enum token_type

static const std::unordered_map<token_type, std::string> gTOKEN_NAMES = {
  { token_type::kPOSSIBLE_ENTITY, "kPOSSIBLE_ENTITY" },
  { token_type::kERROR, "kERROR" },
  { token_type::kNUMBER, "kNUMBER" },
  { token_type::kCHAR_LITERAL, "kCHAR_LITERAL" },
  { token_type::kSTRING_LITERAL, "kSTRING_LITERAL" },
  { token_type::kOPENING_DELIMITER, "kOPENING_DELIMITER" },
  { token_type::kCLOSING_DELIMITER, "kCLOSING_DELIMITER" },
  { token_type::kTERMINATOR, "kTERMINATOR" },
  { token_type::kSEPARATOR, "kSEPARATOR" },
  { token_type::kNULLPTR, "kNULLPTR" },
  { token_type::kDEFINE, "kDEFINE" },
  { token_type::kTHIS, "kTHIS" },
  { token_type::kCLASS, "kCLASS" },
  { token_type::kINTERFACE, "kINTERFACE" },
  { token_type::kUNION, "kUNION" },
  { token_type::kENUM, "kENUM" },
  { token_type::kFUNCTION, "kFUNCTION" },
  { token_type::kRETURN, "kRETURN" },
  { token_type::kYIELD, "kYIELD" },
  { token_type::kMODULE, "kMODULE" },
  { token_type::kIMPORT, "kIMPORT" },
  { token_type::kVARIABLE, "kVARIABLE" },
  { token_type::kAUTO, "kAUTO" },
  { token_type::kTYPE, "kTYPE" },
  { token_type::kTYPE_MODIFIER, "kTYPE_MODIFIER" },
  { token_type::kTEMPLATE, "kTEMPLATE" },
  { token_type::kTYPENAME, "kTYPENAME" },
  { token_type::kAS, "kAS" },
  { token_type::kUSING, "kUSING" },
  { token_type::kTYPEDEF, "kTYPEDEF" },
  { token_type::kIF, "kIF" },
  { token_type::kELSE, "kELSE" },
  { token_type::kMATCH, "kMATCH" },
  { token_type::kFOR, "kFOR" },
  { token_type::kDO, "kDO" },
  { token_type::kWHILE, "kWHILE" },
  { token_type::kNOT, "kNOT" },
  { token_type::kOR, "kOR" },
  { token_type::kAND, "kAND" },
  { token_type::kPUBLIC, "kPUBLIC" },
  { token_type::kPROTECTED, "kPROTECTED" },
  { token_type::kPRIVATE, "kPRIVATE" },
  { token_type::kALIGNAS, "kALIGNAS" },
  { token_type::kALIGNOF, "kALIGNOF" },
  { token_type::kSIZEOF, "kSIZEOF" },
  { token_type::kRANGE, "kRANGE" },
  { token_type::kELLIPSIS, "kELLIPSIS" },
  { token_type::kEXTERN, "kEXTERN" },
  { token_type::kOPERATOR, "kOPERATOR" },
  { token_type::kTHROW, "kTHROW" },
  { token_type::kASM, "kASM" },
  { token_type::kYIELD, "kYIELD" },
  { token_type::kUNSAFE, "kUNSAFE" },
  { token_type::kEND_OF_FILE, "kEND_OF_FILE" },
};

} // namespace syntax
