#include "gtest/gtest.h"

#include "syntax/token.hpp"
#include "syntax/token_type.hpp"

#include <string>

#define ASSERT_TOKEN_EQ(l, f, v, t) \
{\
  syntax::token tok(l, f, v);\
  ASSERT_EQ(tok.line(), l);\
  ASSERT_EQ(tok.filename(), f);\
  ASSERT_EQ(tok.value(), v);\
  ASSERT_EQ(syntax::gTOKEN_NAMES.at(tok.type()), syntax::gTOKEN_NAMES.at(t));\
}

#define ASSERT_TOKEN_TYPE_EQ(v, t) ASSERT_TOKEN_EQ(0, "test", v, t)

TEST(token, binary) {
  ASSERT_TOKEN_TYPE_EQ("0b1101", syntax::token_type::kNUMBER);
  ASSERT_TOKEN_TYPE_EQ("0B1101", syntax::token_type::kNUMBER);
  ASSERT_TOKEN_TYPE_EQ("0b2101", syntax::token_type::kERROR);
}

TEST(token, octal) {
  ASSERT_TOKEN_TYPE_EQ("0o804", syntax::token_type::kNUMBER);
  ASSERT_TOKEN_TYPE_EQ("0O804", syntax::token_type::kNUMBER);
  ASSERT_TOKEN_TYPE_EQ("0o904", syntax::token_type::kERROR);
}

TEST(token, decimal) {
  ASSERT_TOKEN_TYPE_EQ("100", syntax::token_type::kNUMBER);
  ASSERT_TOKEN_TYPE_EQ("1,000", syntax::token_type::kNUMBER);
  ASSERT_TOKEN_TYPE_EQ("1,000.00", syntax::token_type::kNUMBER);
  ASSERT_TOKEN_TYPE_EQ("1,0,00", syntax::token_type::kERROR);
  ASSERT_TOKEN_TYPE_EQ("3.14.5", syntax::token_type::kERROR);
  ASSERT_TOKEN_TYPE_EQ("10a", syntax::token_type::kERROR);
  ASSERT_TOKEN_TYPE_EQ(",100", syntax::token_type::kERROR);
}

TEST(token, hex) {
  ASSERT_TOKEN_TYPE_EQ("0xDEADBEEF", syntax::token_type::kNUMBER);
  ASSERT_TOKEN_TYPE_EQ("0XDEADBEEF", syntax::token_type::kNUMBER);
  ASSERT_TOKEN_TYPE_EQ("0xdeadbeef", syntax::token_type::kNUMBER);
  ASSERT_TOKEN_TYPE_EQ("0Xdeadbeef", syntax::token_type::kNUMBER);
  ASSERT_TOKEN_TYPE_EQ("0xDEADBEEG", syntax::token_type::kERROR);
}

TEST(token, char) {
  ASSERT_TOKEN_TYPE_EQ("\'c\'", syntax::token_type::kCHAR_LITERAL);
  ASSERT_TOKEN_TYPE_EQ("\'ERROR", syntax::token_type::kERROR);
}

TEST(token, string) {
  ASSERT_TOKEN_TYPE_EQ("\"Hi!\"", syntax::token_type::kSTRING_LITERAL);
  ASSERT_TOKEN_TYPE_EQ("\"ERROR", syntax::token_type::kERROR);
}

TEST(token, comma) { ASSERT_TOKEN_TYPE_EQ(",", syntax::token_type::kSEPARATOR); }

TEST(token, semicolon) { ASSERT_TOKEN_TYPE_EQ(";", syntax::token_type::kTERMINATOR); }

TEST(token, delimiter) {
  ASSERT_TOKEN_TYPE_EQ("[", syntax::token_type::kOPENING_DELIMITER);
  ASSERT_TOKEN_TYPE_EQ("]", syntax::token_type::kCLOSING_DELIMITER);
  ASSERT_TOKEN_TYPE_EQ("{", syntax::token_type::kOPENING_DELIMITER);
  ASSERT_TOKEN_TYPE_EQ("}", syntax::token_type::kCLOSING_DELIMITER);
  ASSERT_TOKEN_TYPE_EQ("(", syntax::token_type::kOPENING_DELIMITER);
  ASSERT_TOKEN_TYPE_EQ(")", syntax::token_type::kCLOSING_DELIMITER);
}

TEST(token, keyword) {
  ASSERT_TOKEN_TYPE_EQ("if", syntax::token_type::kIF);
  ASSERT_TOKEN_TYPE_EQ("else", syntax::token_type::kELSE);
  ASSERT_TOKEN_TYPE_EQ("ele", syntax::token_type::kPOSSIBLE_ENTITY);
}
