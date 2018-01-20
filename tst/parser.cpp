#include "gtest/gtest.h"

#include "syntax/lexer.hpp"
#include "syntax/parser.hpp"

#include <list>
#include <string>
#include <iostream>

class test_parser : public syntax::parser {
private:
protected:
public:
private:
protected:
public:
  using syntax::parser::is_valid_type;
  using syntax::parser::is_valid_value;
  using syntax::parser::is_valid_token;
  using syntax::parser::parse_type;
  using syntax::parser::parse_parentheses;
  using syntax::parser::try_read_modifiers;
  using syntax::parser::parse_function;
  using syntax::parser::parse_variable;
  using syntax::parser::parse_identifier;
  using syntax::parser::parse_binary_operation_expression;
  using syntax::parser::parse_primary;
  using syntax::parser::parse_expression;
  using syntax::parser::parse_program;
  using syntax::parser::parse_sequence;
  using syntax::parser::parse;
}; // class parser

TEST(parse, nothing) {
  syntax::lexer l;
  syntax::parser p;
  ASSERT_TRUE(l.tokens().size() == 0);
  ASSERT_EQ(p.parse(l.tokens()), nullptr);
}

TEST(parse, is_valid_type) {
  test_parser p;
  syntax::token t(0, "test", "3.14");
  std::list<syntax::token> l;
  l.push_back(t);
  auto it = l.begin();
  ASSERT_TRUE(p.is_valid_type(it, syntax::token_type::kNUMBER));
  ASSERT_FALSE(p.is_valid_type(it, syntax::token_type::kERROR));
}

TEST(parse, is_valid_value) {
  test_parser p;
  syntax::token t(0, "test", "3.14");
  std::list<syntax::token> l;
  l.push_back(t);
  auto it = l.begin();
  ASSERT_TRUE(p.is_valid_value(it, "3.14"));
  ASSERT_FALSE(p.is_valid_value(it, "cat"));
}

TEST(parse, is_valid_token) {
  test_parser p;
  syntax::token t(0, "test", "3.14");
  std::list<syntax::token> l;
  l.push_back(t);
  auto it = l.begin();
  ASSERT_TRUE(p.is_valid_token(it, syntax::token_type::kNUMBER, "3.14"));
  ASSERT_FALSE(p.is_valid_token(it, syntax::token_type::kERROR, "cat"));
}

TEST(parse, file) {
  syntax::lexer l;
  l.lex("/Users/robertbaldwin/Documents/GitHub/cat/tst/basic_main.cat");

  ASSERT_TRUE(l.tokens().size() > 0);
  syntax::parser p;
  auto res = p.parse(l.tokens());
  if (res) res->print();
  ASSERT_FALSE(true); // should fail until this is fleshed out
}
