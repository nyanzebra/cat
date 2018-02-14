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
  using syntax::parser::parse_block;
  using syntax::parser::parse_if;
  using syntax::parser::parse_bool;
  using syntax::parser::parse_char;
  using syntax::parser::parse_integer;
  using syntax::parser::parse_unsigned_integer;
  using syntax::parser::parse_float;
  using syntax::parser::parse;
}; // class test_parser

TEST(parse, nothing) {
  syntax::lexer l;
  test_parser p;
  ASSERT_TRUE(l.tokens().empty());
  auto res = p.parse(l.tokens());
  ASSERT_EQ(nullptr, res);
}

TEST(parse, is_valid_type) {
  test_parser p;
  syntax::token t(0, "test", "3.14");
  std::list<syntax::token> l;
  l.push_back(t);
  auto it = l.begin();
  ASSERT_TRUE(p.is_valid_type(it, syntax::token_type::kFLOAT_LITERAL));
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
  ASSERT_TRUE(p.is_valid_token(it, syntax::token_type::kFLOAT_LITERAL, "3.14"));
  ASSERT_FALSE(p.is_valid_token(it, syntax::token_type::kERROR, "cat"));
}

TEST(parse, parse_bool) {
  test_parser p;
  std::list<syntax::token> l;
  auto res = p.parse_bool(l.cbegin(), l.cend());
  EXPECT_EQ(nullptr, res);

  syntax::token t(0, "test", "true");
  l.push_back(t);
  res = p.parse_bool(l.cbegin(), l.cend());
  ASSERT_NE(nullptr, res);
  EXPECT_TRUE(res->value());

  l.clear();
  syntax::token u(0, "test", "false");
  l.push_back(u);
  res = p.parse_bool(l.cbegin(), l.cend());
  ASSERT_NE(nullptr, res);
  EXPECT_FALSE(res->value());
}

TEST(parse, parse_char) {
  test_parser p;
  std::list<syntax::token> l;
  auto res = p.parse_char(l.cbegin(), l.cend());
  ASSERT_EQ(nullptr, res);

  syntax::token t(0, "test", "\'a\'");
  l.push_back(t);
  res = p.parse_char(l.cbegin(), l.cend());
  ASSERT_NE(nullptr, res);
  EXPECT_EQ(res->value(), 'a');

  l.clear();
  syntax::token u(0, "test", "\'z\'");
  l.push_back(u);
  res = p.parse_char(l.cbegin(), l.cend());
  ASSERT_NE(nullptr, res);
  EXPECT_EQ(res->value(), 'z');
}

TEST(parse, parse_integer) {
  test_parser p;
  std::list<syntax::token> l;
  auto res = p.parse_integer(l.cbegin(), l.cend());
  ASSERT_EQ(nullptr, res);

  syntax::token t(0, "test", "0");
  l.push_back(t);
  res = p.parse_integer(l.cbegin(), l.cend());
  ASSERT_NE(nullptr, res);
  EXPECT_EQ(res->value(), 0);

  l.clear();
  syntax::token u(0, "test", "1,000");
  l.push_back(u);
  res = p.parse_integer(l.cbegin(), l.cend());
  ASSERT_NE(nullptr, res);
  EXPECT_EQ(res->value(), 1'000);
}

TEST(parse, parse_unsigned_integer) {
  test_parser p;
  std::list<syntax::token> l;
  auto res = p.parse_unsigned_integer(l.cbegin(), l.cend());
  ASSERT_EQ(nullptr, res);

  syntax::token t(0, "test", "0u");
  l.push_back(t);
  res = p.parse_unsigned_integer(l.cbegin(), l.cend());
  ASSERT_NE(nullptr, res);
  EXPECT_EQ(res->value(), 0u);

  l.clear();
  syntax::token u(0, "test", "1,000u");
  l.push_back(u);
  res = p.parse_unsigned_integer(l.cbegin(), l.cend());
  ASSERT_NE(nullptr, res);
  EXPECT_EQ(res->value(), 1'000u);
}

TEST(parse, parse_float) {
  test_parser p;
  std::list<syntax::token> l;
  auto res = p.parse_float(l.cbegin(), l.cend());
  ASSERT_EQ(nullptr, res);

  syntax::token t(0, "test", "3.14");
  l.push_back(t);
  res = p.parse_float(l.cbegin(), l.cend());
  ASSERT_NE(nullptr, res);
  EXPECT_EQ(res->value(), 3.14);

  l.clear();
  syntax::token u(0, "test", "2.718281828459045");
  l.push_back(u);
  res = p.parse_float(l.cbegin(), l.cend());
  ASSERT_NE(nullptr, res);
  EXPECT_EQ(res->value(), 2.718281828459045);
}

TEST(parse, try_read_modifiers) {
  test_parser p;

  syntax::token u(0, "test", "mutable");
  EXPECT_EQ(syntax::token_type::kTYPE_MODIFIER, u.type());
  syntax::token v(0, "test", "volatile");
  EXPECT_EQ(syntax::token_type::kTYPE_MODIFIER, v.type());
  syntax::token w(0, "test", "static");
  EXPECT_EQ(syntax::token_type::kTYPE_MODIFIER, w.type());
  syntax::token x(0, "test", "extern");
  EXPECT_EQ(syntax::token_type::kTYPE_MODIFIER, x.type());

  auto mods = syntax::modifiers::kNONE;
  std::list<syntax::token> l;
  auto res = p.try_read_modifiers(l.cbegin(), l.cend());
  EXPECT_EQ(mods, res.first);

  l.push_back(u);
  mods = syntax::modifiers::kMUTABLE;
  EXPECT_EQ(true, p.is_valid_value(l.begin(), "mutable"));
  res = p.try_read_modifiers(l.cbegin(), l.cend());
  EXPECT_EQ(mods, res.first);

  l.push_back(v);
  mods |= syntax::modifiers::kVOLATILE;
  res = p.try_read_modifiers(l.cbegin(), l.cend());
  EXPECT_EQ(mods, res.first);

  l.push_back(w);
  mods |= syntax::modifiers::kSTATIC;
  res = p.try_read_modifiers(l.cbegin(), l.cend());
  EXPECT_EQ(mods, res.first);

  l.push_back(x);
  mods |= syntax::modifiers::kEXTERN;
  res = p.try_read_modifiers(l.cbegin(), l.cend());
  EXPECT_EQ(mods, res.first);
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
  ASSERT_EQ(nullptr, res);

  auto mods = syntax::modifiers::kNONE;
  auto t_only = syntax::ast_type("flt32", mods);

  l.push_front(t);
  res = p.parse_type(l.cbegin(), l.cend());
  ASSERT_NE(nullptr, res);
  EXPECT_EQ(t_only.name(), res->name());
  EXPECT_EQ(t_only.modifiers(), res->modifiers());

  mods = syntax::modifiers::kMUTABLE;
  auto tu_only = syntax::ast_type("flt32", mods);

  l.push_front(u);
  res = p.parse_type(l.cbegin(), l.cend());
  ASSERT_NE(nullptr, res);
  EXPECT_EQ(tu_only.name(), res->name());
  EXPECT_EQ(tu_only.modifiers(), res->modifiers());

  mods |= syntax::modifiers::kVOLATILE;
  auto tuv_only = syntax::ast_type("flt32", mods);

  l.push_front(v);
  res = p.parse_type(l.cbegin(), l.cend());
  ASSERT_NE(nullptr, res);
  EXPECT_EQ(tuv_only.name(), res->name());
  EXPECT_EQ(tuv_only.modifiers(), res->modifiers());

  mods |= syntax::modifiers::kSTATIC;
  auto tuvw_only = syntax::ast_type("flt32", mods);

  l.push_front(w);
  res = p.parse_type(l.cbegin(), l.cend());
  ASSERT_NE(nullptr, res);
  EXPECT_EQ(tuvw_only.name(), res->name());
  EXPECT_EQ(tuvw_only.modifiers(), res->modifiers());

  mods |= syntax::modifiers::kEXTERN;
  auto tuvwx_only = syntax::ast_type("flt32", mods);

  l.push_front(x);
  res = p.parse_type(l.cbegin(), l.cend());
  ASSERT_NE(nullptr, res);
  EXPECT_EQ(tuvwx_only.name(), res->name());
  EXPECT_EQ(tuvwx_only.modifiers(), res->modifiers());
}

// TEST(parse, if) {
//   test_parser p;
//
//   std::list<syntax::token> l;
//
//   auto res = p.parse_if(l.begin(), l.end());
//   ASSERT_EQ(nullptr, res);
//
//   l.emplace_back(0, "test", "if");
//   l.emplace_back(0, "test", "(");
//   l.emplace_back(0, "test", "true");
//   l.emplace_back(0, "test", ")");
//
//   auto expect = std::make_unique<syntax::ast_if>()
//
//   ASSERT_NE(nullptr, res)
// }

TEST(parse, parse_program) {
  test_parser p;
  syntax::token t(0, "test", "flt32");
  std::list<syntax::token> l;

  auto res = p.parse_program(l.cbegin(), l.cend());
  ASSERT_EQ(nullptr, res);

  l.push_back(t);
  res = p.parse_program(l.cbegin(), l.cend());
  //TODO: change when implemented more
  ASSERT_EQ(nullptr, res);

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
