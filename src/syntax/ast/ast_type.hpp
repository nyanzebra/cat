#pragma once

#include "ast_expression.hpp"

#include "deps/std.hpp"

namespace syntax {

template<typename T>
class ast_type : public ast_expression {
private:
  T _value;
protected:
public:
private:
protected:
public:
  ast_type(const T& value) : _value(value) {}
  //ast_type(T&& value) : _value(std::move(value)) {}
  virtual ~ast_type() = default;

  operator T() { return _value; }
  operator T() const { return _value; }

  virtual void print() { std::cout << _value; }

  const T& value() const { return _value; }
  void value(const T& value) { _value = value; }
  //void value(T&& value) { _value = std::move(value); }

  template<typename Visitor, typename = std::enable_if_t<std::is_member_function_pointer_v<decltype(&Visitor::visit)>>>
  typename Visitor::return_type accept(std::unique_ptr<Visitor> visitor) { return visitor->visit(std::make_unique<decltype(this)>(this)); }
};

} // namespace syntax
