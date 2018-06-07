#include "gtest/gtest.h"

#include "syntax/lexer.hpp"
#include "syntax/parser.hpp"
#include "syntax/visitor/code_generator_visitor.hpp"

#include "deps/std.hpp"

TEST(code_generator_visitor, generate_basic_main) {
  using namespace syntax;
  using namespace llvm;
  std::list<std::string> inputs;
  inputs.push_back("/Users/robertbaldwin/Documents/GitHub/cat/tst/basic_main.cat");
  lexer l;
  l.lex(std::move(inputs));
  parser p;
  auto program = p.parse(l.tokens());
  code_generator_visitor visitor;
  visitor.initialize();
  visitor.create_compile_units(inputs);
  program->accept(&visitor, {""});
  visitor.finalize("output");
}
