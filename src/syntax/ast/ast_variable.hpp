#pragma once

#include "ast_expression.hpp"
#include "ast_type.hpp"
#include "modifiers.hpp"

namespace syntax {

// variable TODO: add value
class ast_variable final : public ast_expression {
private:
  std::string _name;
  std::unique_ptr<ast_type> _type;
  std::unique_ptr<ast_expression> _value;
protected:
public:
private:
protected:
public:
  template<typename T, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  ast_variable(T&& name, std::unique_ptr<ast_type> type, std::unique_ptr<ast_expression> value = nullptr) : _name(std::move(name)), _type(std::move(type)), _value(std::move(value)) {}

  const std::string& name() const { return _name; }
  const std::unique_ptr<ast_type>& type() const { return _type; }
  const std::unique_ptr<ast_expression>& value() const { return _value; }

  void print(size_t tabs) override {
    _type->print(tabs);
    std::cout << ' ' << _name;
    if (_value) {
      std::cout << " = ";
      _value->print(0);
    }
    std::cout << ';' << std::endl;
  }

  template<typename Visitor, typename = std::enable_if_t<std::is_member_function_pointer<decltype(&Visitor::visit)>::value>>
  typename Visitor::return_type accept(std::unique_ptr<Visitor> visitor) { return visitor->visit(std::make_unique<decltype(this)>(this)); }
};

} // namespace syntax
