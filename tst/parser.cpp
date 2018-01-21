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
}; // class test_parser

TEST(parse, nothing) {
  syntax::lexer l;
  test_parser p;
  ASSERT_TRUE(l.tokens().empty());
  auto res = p.parse(l.tokens());
  ASSERT_EQ(res.get(), nullptr);
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

TEST(parse, parse_type) {
  test_parser p;

  syntax::token t(0, "test", "flt32");
  syntax::token u(0, "test", "mutable");
  syntax::token v(0, "test", "volatile");
  syntax::token w(0, "test", "static");
  syntax::token x(0, "test", "extern");

  std::list<syntax::token> l;
  auto res = p.parse_type(l.cbegin(), l.cend());
  ASSERT_EQ(res.get(), nullptr);

  auto mods = syntax::modifiers::kNONE;
  auto t_only = syntax::ast_type("flt32", mods);

  mods = syntax::modifiers::kMUTABLE;
  auto tu_only = syntax::ast_type("flt32", mods);

  mods |= syntax::modifiers::kVOLATILE;
  auto tuv_only = syntax::ast_type("flt32", mods);

  mods |= syntax::modifiers::kSTATIC;
  auto tuvw_only = syntax::ast_type("flt32", mods);

  mods |= syntax::modifiers::kEXTERN;
  auto tuvwx_only = syntax::ast_type("flt32", mods);

  l.push_front(t);
  res = p.parse_type(l.cbegin(), l.cend());
  ASSERT_NE(res, nullptr);
  EXPECT_EQ(*(res.get()), t_only);

  l.push_front(u);
  res = p.parse_type(l.cbegin(), l.cend());
  ASSERT_NE(res, nullptr);
  EXPECT_EQ(*res, tu_only);

  l.push_front(v);
  res = p.parse_type(l.cbegin(), l.cend());
  ASSERT_NE(res, nullptr);
  EXPECT_EQ(*res, tuv_only);

  l.push_front(w);
  res = p.parse_type(l.cbegin(), l.cend());
  ASSERT_NE(res, nullptr);
  EXPECT_EQ(*res, tuvw_only);

  l.push_front(x);
  res = p.parse_type(l.cbegin(), l.cend());
  ASSERT_NE(res, nullptr);
  EXPECT_EQ(*res, tuvwx_only);
}

TEST(parse, parse_program) {
  test_parser p;
  syntax::token t(0, "test", "flt32");
  std::list<syntax::token> l;

  auto res = p.parse_program(l.cbegin(), l.cend());
  ASSERT_EQ(res.get(), nullptr);

  l.push_back(t);
  res = p.parse_program(l.cbegin(), l.cend());
  //TODO: change when implemented more
  ASSERT_EQ(res.get(), nullptr);

}

TEST(parse, file) {
  syntax::lexer l;
  l.lex("../basic_main.cat");

  ASSERT_TRUE(l.tokens().size() > 0);
  syntax::parser p;
  auto res = p.parse(l.tokens());
  if (res) res->print();
  ASSERT_FALSE(false); // TODO: change when implemented
}
