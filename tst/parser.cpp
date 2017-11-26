#include "gtest/gtest.h"

#include "syntax/lexer.hpp"
#include "syntax/parser.hpp"

#include <list>
#include <string>

TEST(parse, file) {
  syntax::lexer l;
  l.lex("/Users/robertbaldwin/Documents/GitHub/cat/tst/basic_main.cat");

  syntax::parser p;
  auto res = p.parse(l.tokens());

  res->print();
}
