#include "gtest/gtest.h"

#include "syntax/lexer.hpp"

#include <list>
#include <string>

TEST(lex, nothing) {
  syntax::lexer l;

  ASSERT_EQ(l.tokens().size(), 0);
}

TEST(lex, file) {
  syntax::lexer l;
  l.lex("../basic_main.cat");

  std::list<std::string> tokens = {
    "import",
    "std",
    "{",
    "io",
    ",",
    "string",
    ",",
    "vector",
    "}",
    "int64",
    "main",
    "(",
    "vector",
    "<",
    "string",
    ">",
    "args",
    ")",
    "{",
    "flt32",
    "f",
    ";",
    "volatile",
    "flt32",
    "g",
    ";",
    "mutable",
    "volatile",
    "flt32",
    "h",
    ";",
    "static",
    "mutable",
    "volatile",
    "flt32",
    "i",
    ";",
    "extern",
    "static",
    "mutable",
    "volatile",
    "flt32",
    "j",
    ";",
    "std",
    ":",
    ":",
    "io",
    ":",
    ":",
    "out",
    "<",
    "<",
    "\"Args: \"",
    "<",
    "<",
    "args",
    "<",
    "<",
    "std",
    ":",
    ":",
    "io",
    ":",
    ":",
    "endl",
    ";",
    "std",
    ":",
    ":",
    "io",
    ":",
    ":",
    "out",
    "<",
    "<",
    "\"Eval (2 * (3 + 4)** 5)\"",
    "<",
    "<",
    "(",
    "2",
    "*",
    "(",
    "3",
    "+",
    "4",
    ")",
    "*",
    "*",
    "5",
    ")",
    "<",
    "<",
    "std",
    ":",
    ":",
    "io",
    ":",
    ":",
    "endl",
    ";",
    "}"
  };

  ASSERT_EQ(l.tokens().size(), tokens.size());
  auto a_it = l.tokens().begin();
  auto b_it = tokens.begin();
  for (auto i = 0u; i < tokens.size(); ++i) {
    ASSERT_EQ(a_it->value(), *b_it);
    ASSERT_NE(a_it->type(), syntax::token_type::kERROR);
  }
}

TEST(lex, files) {
  ASSERT_FALSE(false); // TODO: add more test files
}
