#include "gtest/gtest.h"

#include "syntax/lexer.hpp"
#include "syntax/parser.hpp"

#include "deps/std.hpp"

// bool expect_output(std::string expect, std::function<void()> fn) {
//   testing::internal::CaptureStdout();
//   fn();
//   std::string actual = testing::internal::GetCapturedStdout();
//   EXTECT_EQ(expect, actual)
// }
//
// #define EXPECT_OUTPUT(expect, fn) expect_output(expect, fn);

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
  using syntax::parser::parse_string;
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
  std::stringstream stream;
  test_parser p;
  std::list<syntax::token> l;
  auto start = l.cbegin();
  auto res = p.parse_bool(start, l.cend());
  EXPECT_EQ(nullptr, res);

  syntax::token t(0, "test", "true");
  l.push_back(t);
  start = l.cbegin();
  res = p.parse_bool(start, l.cend());
  ASSERT_NE(nullptr, res);
  EXPECT_TRUE(res->value());
  res->print(stream);
  EXPECT_EQ("true", stream.str());
  stream.str("");

  l.clear();
  syntax::token u(0, "test", "false");
  l.push_back(u);
  start = l.cbegin();
  res = p.parse_bool(start, l.cend());
  ASSERT_NE(nullptr, res);
  EXPECT_FALSE(res->value());
  res->print(stream);
  EXPECT_EQ("false", stream.str());
  stream.str("");

  l.clear();
  syntax::token v(0, "test", "3.14");
  l.push_back(v);
  start = l.cbegin();
  res = p.parse_bool(start, l.cend());
  ASSERT_EQ(nullptr, res);
}

TEST(parse, parse_char) {
  std::stringstream stream;
  test_parser p;
  std::list<syntax::token> l;
  auto start = l.cbegin();
  auto res = p.parse_char(start, l.cend());
  ASSERT_EQ(nullptr, res);

  syntax::token t(0, "test", "\'a\'");
  l.push_back(t);
  start = l.cbegin();
  res = p.parse_char(start, l.cend());
  ASSERT_NE(nullptr, res);
  EXPECT_EQ('a', res->value());
  res->print(stream);
  EXPECT_EQ("a", stream.str());
  stream.str("");

  l.clear();
  syntax::token u(0, "test", "\'z\'");
  l.push_back(u);
  start = l.cbegin();
  res = p.parse_char(start, l.cend());
  ASSERT_NE(nullptr, res);
  EXPECT_EQ('z', res->value());
  res->print(stream);
  EXPECT_EQ("z", stream.str());
  stream.str("");

  l.clear();
  syntax::token v(0, "test", "true");
  l.push_back(v);
  start = l.cbegin();
  res = p.parse_char(start, l.cend());
  ASSERT_EQ(nullptr, res);
}

TEST(parse, parse_integer) {
  std::stringstream stream;
  test_parser p;
  std::list<syntax::token> l;
  auto start = l.cbegin();
  auto res = p.parse_integer(start, l.cend());
  ASSERT_EQ(nullptr, res);

  syntax::token t(0, "test", "0");
  l.push_back(t);
  start = l.cbegin();
  res = p.parse_integer(start, l.cend());
  ASSERT_NE(nullptr, res);
  EXPECT_EQ(0, res->value());
  res->print(stream);
  EXPECT_EQ("0", stream.str());
  stream.str("");

  l.clear();
  syntax::token u(0, "test", "1,000");
  l.push_back(u);
  start = l.cbegin();
  res = p.parse_integer(start, l.cend());
  ASSERT_NE(nullptr, res);
  EXPECT_EQ(1'000, res->value());
  res->print(stream);
  EXPECT_EQ("1000", stream.str());
  stream.str("");

  l.clear();
  syntax::token v(0, "test", "true");
  l.push_back(v);
  start = l.cbegin();
  res = p.parse_unsigned_integer(start, l.cend());
  ASSERT_EQ(nullptr, res);
}

TEST(parse, parse_unsigned_integer) {
  std::stringstream stream;
  test_parser p;
  std::list<syntax::token> l;
  auto start = l.cbegin();
  auto res = p.parse_unsigned_integer(start, l.cend());
  ASSERT_EQ(nullptr, res);

  syntax::token t(0, "test", "0u");
  l.push_back(t);
  start = l.cbegin();
  res = p.parse_unsigned_integer(start, l.cend());
  ASSERT_NE(nullptr, res);
  EXPECT_EQ(res->value(), 0u);

  l.clear();
  syntax::token u(0, "test", "1,000u");
  l.push_back(u);
  start = l.cbegin();
  res = p.parse_unsigned_integer(start, l.cend());
  ASSERT_NE(nullptr, res);
  EXPECT_EQ(res->value(), 1'000u);

  l.clear();
  syntax::token v(0, "test", "true");
  l.push_back(v);
  start = l.cbegin();
  res = p.parse_unsigned_integer(start, l.cend());
  ASSERT_EQ(nullptr, res);
}

TEST(parse, parse_float) {
  test_parser p;
  std::list<syntax::token> l;
  auto start = l.cbegin();
  auto res = p.parse_float(start, l.cend());
  ASSERT_EQ(nullptr, res);

  syntax::token t(0, "test", "3.14");
  l.push_back(t);
  start = l.cbegin();
  res = p.parse_float(start, l.cend());
  ASSERT_NE(nullptr, res);
  EXPECT_EQ(res->value(), 3.14);

  l.clear();
  syntax::token u(0, "test", "2.718281828459045");
  l.push_back(u);
  start = l.cbegin();
  res = p.parse_float(start, l.cend());
  ASSERT_NE(nullptr, res);
  EXPECT_EQ(res->value(), 2.718281828459045);

  l.clear();
  syntax::token v(0, "test", "true");
  l.push_back(v);
  start = l.cbegin();
  res = p.parse_float(start, l.cend());
  ASSERT_EQ(nullptr, res);
}

TEST(parse, parse_string) {
  test_parser p;
  std::list<syntax::token> l;
  auto start = l.cbegin();
  auto res = p.parse_string(start, l.cend());
  ASSERT_EQ(nullptr, res);

  syntax::token t(0, "test", "\"a\"");
  l.push_back(t);
  start = l.cbegin();
  res = p.parse_string(start, l.cend());
  ASSERT_NE(nullptr, res);
  EXPECT_EQ(res->value(), "\"a\"");

  l.clear();
  syntax::token u(0, "test", "\"apple\"");
  l.push_back(u);
  start = l.cbegin();
  res = p.parse_string(start, l.cend());
  ASSERT_NE(nullptr, res);
  EXPECT_EQ(res->value(), "\"apple\"");

  l.clear();
  syntax::token v(0, "test", "true");
  l.push_back(v);
  start = l.cbegin();
  res = p.parse_string(start, l.cend());
  ASSERT_EQ(nullptr, res);
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
  auto start = l.cbegin();
  auto res = p.try_read_modifiers(start, l.cend());
  EXPECT_EQ(mods, res);

  l.push_back(u);
  mods = syntax::modifiers::kMUTABLE;
  start = l.cbegin();
  res = p.try_read_modifiers(start, l.cend());
  EXPECT_EQ(mods, res);

  l.push_back(v);
  mods |= syntax::modifiers::kVOLATILE;
  start = l.cbegin();
  res = p.try_read_modifiers(start, l.cend());
  EXPECT_EQ(mods, res);

  l.push_back(w);
  mods |= syntax::modifiers::kSTATIC;
  start = l.cbegin();
  res = p.try_read_modifiers(start, l.cend());
  EXPECT_EQ(mods, res);

  l.push_back(x);
  mods |= syntax::modifiers::kEXTERN;
  start = l.cbegin();
  res = p.try_read_modifiers(start, l.cend());
  EXPECT_EQ(mods, res);
}

TEST(parse, parse_type) {
  test_parser p;

  syntax::token t(0, "test", "flt32");
  syntax::token u(0, "test", "mutable");
  syntax::token v(0, "test", "volatile");
  syntax::token w(0, "test", "static");
  syntax::token x(0, "test", "extern");

  std::list<syntax::token> l;
  auto start = l.cbegin();
  auto res = p.parse_type(start, l.cend());
  ASSERT_EQ(nullptr, res);

  auto mods = syntax::modifiers::kNONE;
  auto t_only = syntax::ast_type("flt32", mods);

  l.push_front(t);
  start = l.cbegin();
  res = p.parse_type(start, l.cend());
  ASSERT_NE(nullptr, res);
  EXPECT_EQ(t_only.name(), res->name());
  EXPECT_EQ(t_only.modifiers(), res->modifiers());

  mods = syntax::modifiers::kMUTABLE;
  auto tu_only = syntax::ast_type("flt32", mods);

  l.push_front(u);
  start = l.cbegin();
  res = p.parse_type(start, l.cend());
  ASSERT_NE(nullptr, res);
  EXPECT_EQ(tu_only.name(), res->name());
  EXPECT_EQ(tu_only.modifiers(), res->modifiers());

  mods |= syntax::modifiers::kVOLATILE;
  auto tuv_only = syntax::ast_type("flt32", mods);

  l.push_front(v);
  start = l.cbegin();
  res = p.parse_type(start, l.cend());
  ASSERT_NE(nullptr, res);
  EXPECT_EQ(tuv_only.name(), res->name());
  EXPECT_EQ(tuv_only.modifiers(), res->modifiers());

  mods |= syntax::modifiers::kSTATIC;
  auto tuvw_only = syntax::ast_type("flt32", mods);

  l.push_front(w);
  start = l.cbegin();
  res = p.parse_type(start, l.cend());
  ASSERT_NE(nullptr, res);
  EXPECT_EQ(tuvw_only.name(), res->name());
  EXPECT_EQ(tuvw_only.modifiers(), res->modifiers());

  mods |= syntax::modifiers::kEXTERN;
  auto tuvwx_only = syntax::ast_type("flt32", mods);

  l.push_front(x);
  start = l.cbegin();
  res = p.parse_type(start, l.cend());
  ASSERT_NE(nullptr, res);
  EXPECT_EQ(tuvwx_only.name(), res->name());
  EXPECT_EQ(tuvwx_only.modifiers(), res->modifiers());
}

TEST(parse, parse_variable) {
  std::stringstream stream;
  test_parser p;

  std::list<syntax::token> l;
  auto start = l.cbegin();
  auto res = p.parse_variable(start, l.cend());
  ASSERT_EQ(nullptr, res);

  syntax::token t(0, "test", "mutable");
  syntax::token u(0, "test", "flt32");
  syntax::token v(0, "test", "test");
  syntax::token w(0, "test", ";");
  l.push_back(t);
  l.push_back(u);
  l.push_back(v);
  l.push_back(w);
  start = l.cbegin();
  res = p.parse_variable(start, l.cend());
  ASSERT_NE(nullptr, res);
  EXPECT_EQ(v.value(), res->name());
  ASSERT_NE(nullptr, res->type());
  EXPECT_EQ(syntax::modifiers::kMUTABLE, res->type()->modifiers());
  ASSERT_EQ(nullptr, res->value());
  res->print(stream);
  ASSERT_EQ("mutable flt32 test;\n", stream.str());
  stream.str("");

  syntax::token x(0, "test", "=");
  syntax::token y(0, "test", "3.14");
  syntax::token z(0, "test", ";");
  l.pop_back();
  l.push_back(x);
  l.push_back(y);
  l.push_back(z);
  start = l.cbegin();
  res = p.parse_variable(start, l.cend());
  ASSERT_NE(nullptr, res);
  EXPECT_EQ(v.value(), res->name());
  ASSERT_NE(nullptr, res->type());
  EXPECT_EQ(syntax::modifiers::kMUTABLE, res->type()->modifiers());
  ASSERT_NE(nullptr, res->value());
  auto cast = dynamic_cast<syntax::ast_flt64*>(res->value().get());
  ASSERT_NE(nullptr, cast);
  EXPECT_EQ(3.14, cast->value());
  res->print(stream);
  ASSERT_EQ("mutable flt32 test = 3.14;\n", stream.str());
}

TEST(parse, parentheses) {
  std::stringstream stream;
  test_parser p;

  std::list<syntax::token> l;

  auto start = l.cbegin();
  auto res = p.parse_parentheses(start, l.cend());
  ASSERT_EQ(nullptr, res);

  l.emplace_back(0, "test", "(");
  l.emplace_back(0, "test", "true");
  l.emplace_back(0, "test", ")");

  start = l.cbegin();
  res = p.parse_parentheses(start, l.cend());
  ASSERT_NE(nullptr, res);
  std::unique_ptr<syntax::ast_bool> bool_res = std::make_unique<syntax::ast_bool>(dynamic_cast<syntax::ast_bool*>(res.get()));
  ASSERT_NE(nullptr, bool_res);
  EXPECT_TRUE(bool_res->value());
  res->print(stream);
  ASSERT_EQ("true", stream.str());
}

TEST(parse, block) {
  std::stringstream stream;
  test_parser p;

  std::list<syntax::token> l;

  auto start = l.cbegin();
  auto res = p.parse_block(start, l.cend());
  ASSERT_EQ(nullptr, res);

  l.emplace_back(0, "test", "{");
  l.emplace_back(0, "test", "bool");
  l.emplace_back(0, "test", "b");
  l.emplace_back(0, "test", "=");
  l.emplace_back(0, "test", "true");
  l.emplace_back(0, "test", ";");
  l.emplace_back(0, "test", "}");

  start = l.cbegin();
  res = p.parse_block(start, l.cend());
  ASSERT_NE(nullptr, res);
  res->print(stream);
  ASSERT_EQ("{\n\tbool b = true;\n}", stream.str());
}

TEST(parse, if) {
  std::stringstream stream;
  test_parser p;

  std::list<syntax::token> l;

  auto start = l.cbegin();
  auto res = p.parse_if(start, l.cend());
  ASSERT_EQ(nullptr, res);

  l.emplace_back(0, "test", "if");
  l.emplace_back(0, "test", "(");
  l.emplace_back(0, "test", "true");
  l.emplace_back(0, "test", ")");
  l.emplace_back(0, "test", ";");

  auto expect = std::make_unique<syntax::ast_if>(nullptr, nullptr, nullptr);
  start = l.cbegin();
  res = p.parse_if(start, l.cend());
  ASSERT_NE(nullptr, res);
  ASSERT_NE(nullptr, res->condition());
  ASSERT_EQ(nullptr, res->body());
  ASSERT_EQ(nullptr, res->other());
  res->print(stream);
  ASSERT_EQ("if (true);\n", stream.str());
  stream.str("");

  l.pop_back();
  l.emplace_back(0, "test", "{");
  l.emplace_back(0, "test", "bool");
  l.emplace_back(0, "test", "b");
  l.emplace_back(0, "test", "=");
  l.emplace_back(0, "test", "true");
  l.emplace_back(0, "test", ";");
  l.emplace_back(0, "test", "}");
  start = l.cbegin();
  res = p.parse_if(start, l.cend());
  ASSERT_NE(nullptr, res);
  ASSERT_NE(nullptr, res->condition());
  ASSERT_NE(nullptr, res->body());
  ASSERT_EQ(nullptr, res->other());
  res->print(stream);
  ASSERT_EQ("if (true) {\n\tbool b = true;\n}", stream.str());
  stream.str("");


  l.emplace_back(0, "test", "else");
  l.emplace_back(0, "test", "{");
  l.emplace_back(0, "test", "bool");
  l.emplace_back(0, "test", "a");
  l.emplace_back(0, "test", "=");
  l.emplace_back(0, "test", "true");
  l.emplace_back(0, "test", ";");
  l.emplace_back(0, "test", "}");
  start = l.cbegin();
  res = p.parse_if(start, l.cend());
  ASSERT_NE(nullptr, res);
  ASSERT_NE(nullptr, res->condition());
  ASSERT_NE(nullptr, res->body());
  ASSERT_NE(nullptr, res->other());
  res->print(stream);
  ASSERT_EQ("if (true) {\n\tbool b = true;\n} else {\n\tbool a = true;\n}", stream.str());
}

TEST(parse, function) {
  // test_parser p;
  //
  // std::list<syntax::token> l;
  // auto res = p.parse_function_prototype(l.begin(), l.end());
  // ASSERT_EQ(nullptr, res);
}

TEST(parse, parse_program) {
  test_parser p;
  syntax::lexer l;
  auto tokens = l.tokens();
  auto start = tokens.cbegin();
  auto res = p.parse_program(start, tokens.cend());
  ASSERT_EQ(nullptr, res);

  l.lex("../basic_main.cat");
  tokens = l.tokens();
  start = tokens.cbegin();
  res = p.parse_program(start, tokens.cend());
  //TODO: change when implemented more
  ASSERT_FALSE(false);

}

TEST(parse, file) {
  std::stringstream stream;
  syntax::lexer l;
  l.lex("../basic_main.cat");
  ASSERT_TRUE(l.tokens().size() > 0);
  syntax::parser p;
  auto res = p.parse(l.tokens());
  if (res) res->print(stream);
  std::cout << stream.str() << std::endl;
  ASSERT_FALSE(false); // TODO: change when implemented
}
