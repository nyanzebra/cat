#include "gtest/gtest.h"

#include "syntax/token.hpp"
#include "syntax/token_type.hpp"

#include "deps/std.hpp"

#define EXPECT_TOKEN_EQ(l, f, v, t) \
{\
  syntax::token tok(l, f, v);\
  EXPECT_EQ(l, tok.line());\
  EXPECT_EQ(f, tok.filename());\
  EXPECT_EQ(v, tok.value());\
  EXPECT_EQ(t, tok.type());\
  EXPECT_EQ(syntax::gTOKEN_NAMES.at(t), syntax::gTOKEN_NAMES.at(tok.type()));\
}

#define EXPECT_TOKEN_TYPE_EQ(v, t) EXPECT_TOKEN_EQ(0, "test", v, t)

TEST(token, bool) {
  EXPECT_TOKEN_TYPE_EQ("true", syntax::token_type::kBOOL_LITERAL);
  EXPECT_TOKEN_TYPE_EQ("false", syntax::token_type::kBOOL_LITERAL);
}

TEST(token, binary) {
  EXPECT_TOKEN_TYPE_EQ("0b1101", syntax::token_type::kINTEGER_LITERAL);
  EXPECT_TOKEN_TYPE_EQ("0B1101", syntax::token_type::kINTEGER_LITERAL);
  EXPECT_TOKEN_TYPE_EQ("0b2101", syntax::token_type::kERROR);
}

TEST(token, octal) {
  EXPECT_TOKEN_TYPE_EQ("0o804", syntax::token_type::kINTEGER_LITERAL);
  EXPECT_TOKEN_TYPE_EQ("0O804", syntax::token_type::kINTEGER_LITERAL);
  EXPECT_TOKEN_TYPE_EQ("0o904", syntax::token_type::kERROR);
}

TEST(token, decimal) {
  syntax::token tok(0, "test", "100u");
  EXPECT_EQ(0, tok.line());
  EXPECT_EQ("test", tok.filename());
  EXPECT_EQ("100", tok.value());
  EXPECT_EQ(syntax::gTOKEN_NAMES.at(syntax::token_type::kUNSIGNED_INTEGER_LITERAL), syntax::gTOKEN_NAMES.at(tok.type()));

  EXPECT_TOKEN_TYPE_EQ("100", syntax::token_type::kINTEGER_LITERAL);

  syntax::token tok1(0, "test", "1,000");
  EXPECT_EQ(0, tok1.line());
  EXPECT_EQ("test", tok1.filename());
  EXPECT_EQ("1000", tok1.value());
  EXPECT_EQ(syntax::gTOKEN_NAMES.at(syntax::token_type::kINTEGER_LITERAL), syntax::gTOKEN_NAMES.at(tok1.type()));

  syntax::token tok2(0, "test", "1,000u");
  EXPECT_EQ(0, tok2.line());
  EXPECT_EQ("test", tok2.filename());
  EXPECT_EQ("1000", tok2.value());
  EXPECT_EQ(syntax::gTOKEN_NAMES.at(syntax::token_type::kUNSIGNED_INTEGER_LITERAL), syntax::gTOKEN_NAMES.at(tok2.type()));

  syntax::token tok3(0, "test", "1,000.00");
  EXPECT_EQ(0, tok3.line());
  EXPECT_EQ("test", tok3.filename());
  EXPECT_EQ("1000.00", tok3.value());
  EXPECT_EQ(syntax::gTOKEN_NAMES.at(syntax::token_type::kFLOAT_LITERAL), syntax::gTOKEN_NAMES.at(tok3.type()));

  EXPECT_TOKEN_TYPE_EQ("1,000.00u", syntax::token_type::kERROR);
  EXPECT_TOKEN_TYPE_EQ("1,0,00", syntax::token_type::kERROR);
  EXPECT_TOKEN_TYPE_EQ("3.14.5", syntax::token_type::kERROR);
  EXPECT_TOKEN_TYPE_EQ("10a", syntax::token_type::kERROR);
  EXPECT_TOKEN_TYPE_EQ(",100", syntax::token_type::kERROR);
}

TEST(token, hex) {
  EXPECT_TOKEN_TYPE_EQ("0xDEADBEEF", syntax::token_type::kINTEGER_LITERAL);
  EXPECT_TOKEN_TYPE_EQ("0XDEADBEEF", syntax::token_type::kINTEGER_LITERAL);
  EXPECT_TOKEN_TYPE_EQ("0xdeadbeef", syntax::token_type::kINTEGER_LITERAL);
  EXPECT_TOKEN_TYPE_EQ("0Xdeadbeef", syntax::token_type::kINTEGER_LITERAL);
  EXPECT_TOKEN_TYPE_EQ("0xDEADBEEG", syntax::token_type::kERROR);
}

TEST(token, char) {
  EXPECT_TOKEN_TYPE_EQ("\'c\'", syntax::token_type::kCHAR_LITERAL);
  EXPECT_TOKEN_TYPE_EQ("\'ERROR", syntax::token_type::kERROR);
}

TEST(token, string) {
  EXPECT_TOKEN_TYPE_EQ("\"Hi!\"", syntax::token_type::kSTRING_LITERAL);
  EXPECT_TOKEN_TYPE_EQ("\"ERROR", syntax::token_type::kERROR);
}

TEST(token, comma) { EXPECT_TOKEN_TYPE_EQ(",", syntax::token_type::kSEPARATOR); }

TEST(token, semicolon) { EXPECT_TOKEN_TYPE_EQ(";", syntax::token_type::kTERMINATOR); }

TEST(token, delimiter) {
  EXPECT_TOKEN_TYPE_EQ("[", syntax::token_type::kOPENING_DELIMITER);
  EXPECT_TOKEN_TYPE_EQ("]", syntax::token_type::kCLOSING_DELIMITER);
  EXPECT_TOKEN_TYPE_EQ("{", syntax::token_type::kOPENING_DELIMITER);
  EXPECT_TOKEN_TYPE_EQ("}", syntax::token_type::kCLOSING_DELIMITER);
  EXPECT_TOKEN_TYPE_EQ("(", syntax::token_type::kOPENING_DELIMITER);
  EXPECT_TOKEN_TYPE_EQ(")", syntax::token_type::kCLOSING_DELIMITER);
}

TEST(token, keyword) {
  EXPECT_TOKEN_TYPE_EQ("mutable", syntax::token_type::kTYPE_MODIFIER);
  EXPECT_TOKEN_TYPE_EQ("volatile", syntax::token_type::kTYPE_MODIFIER);
  EXPECT_TOKEN_TYPE_EQ("extern", syntax::token_type::kTYPE_MODIFIER);
  EXPECT_TOKEN_TYPE_EQ("static", syntax::token_type::kTYPE_MODIFIER);
  EXPECT_TOKEN_TYPE_EQ("if", syntax::token_type::kIF);
  EXPECT_TOKEN_TYPE_EQ("else", syntax::token_type::kELSE);
  EXPECT_TOKEN_TYPE_EQ("ele", syntax::token_type::kPOSSIBLE_ENTITY);
}
