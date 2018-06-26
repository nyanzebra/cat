#pragma once

#include "ast_expression.hpp"
#include "modifiers.hpp"

#include "deps/std.hpp"

namespace syntax {

class ast_string final : public ast_expression {
private:
  std::string _value;
protected:
public:
private:
protected:
public:
  ast_string(const std::string& value) : _value(value) {}
  template<typename U = std::string, typename = std::enable_if_t<std::is_constructible<std::string, U>::value>>
  ast_string(U&& value) : _value(std::move(value)) {}
  virtual ~ast_string() = default;

  friend bool operator==(const ast_string& lhs, const ast_string& rhs) {
    if (&lhs == &rhs) return true;
    if (lhs._value == rhs._value) return true;
    return false;
  }

  friend bool operator==(ast_string&& lhs, ast_string&& rhs) {
    if (&lhs == &rhs) return true;
    if (lhs._value == rhs._value) return true;
    return false;
  }

  operator std::string() { return _value; }
  operator std::string() const { return _value; }

  std::ostream& print(std::ostream& stream, size_t tabs = 0) override {
    stream << _value;
    return stream;
  }

  const std::string& value() const { return _value; }
  void value(const std::string& value) { _value = value; }
  template<typename U = std::string, typename = std::enable_if_t<std::is_constructible<std::string, U>::value>>
  void value(U&& value) { _value = std::move(value); }

  void* accept(code_generator_visitor* visitor) override;
};

} // namespace syntax
