#pragma once

#include "ast_expression.hpp"

namespace syntax {

class ast_binary_operator : public ast_expression {
private:
  std::string _operator;
  std::unique_ptr<ast_expression> _lhs, _rhs;
protected:
public:
private:
protected:
public:
  template<typename T, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  ast_binary_operator(T&& op, std::unique_ptr<ast_expression> lhs, std::unique_ptr<ast_expression> rhs) : _operator(std::move(op)), _lhs(std::move(lhs)), _rhs(std::move(rhs)) {
    assert(gBINARY_OPERATORS.find(_operator) != gBINARY_OPERATORS.end() && "");
  }

  virtual void print() {
    _lhs->print();
    std::cout << " " << _operator << " ";
    _rhs->print();
  }


  template<typename Visitor, typename = std::enable_if_t<std::is_member_function_pointer_v<decltype(&Visitor::visit)>>>
  typename Visitor::return_type accept(std::unique_ptr<Visitor> visitor) { return visitor->visit(std::make_unique<decltype(this)>(this)); }
};

} // namespace syntax
