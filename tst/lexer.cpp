#include "gtest/gtest.h"

#include "syntax/lexer.hpp"

#include <list>
#include <string>

TEST(lex, nothing) {
  syntax::lexer l;

  ASSERT_EQ(0, l.tokens().size());
}

TEST(lex, file) {
  syntax::lexer l;
  l.lex("../basic_main.cat");

  std::list<std::string> tokens = {
    "int64",
    "main",
    "(",
    ")",
    "{",
    "flt32",
    "f",
    ";",
    "return",
    "0",
    ";",
    "}"
  };

  ASSERT_EQ(l.tokens().size(), tokens.size());
  auto a_it = l.tokens().begin();
  auto b_it = tokens.begin();
  for (auto i = 0u; i < tokens.size(); ++i) {
    ASSERT_EQ(*b_it, a_it->value());
    ASSERT_NE(syntax::token_type::kERROR, a_it->type());
  }
}

TEST(lex, files) {
  ASSERT_FALSE(false); // TODO: add more test files
}
