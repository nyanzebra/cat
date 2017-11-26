#pragma once

#include "ast_expression.hpp"

namespace syntax {

class ast_unary_operator : public ast_expression {
private:
  std::string _operator;
  std::unique_ptr<ast_expression> _rhs;
protected:
public:
private:
protected:
public:
  template<
    typename T,
    typename = std::enable_if_t<
      std::is_constructible_v<
        std::string,
        T
      >
    >
  >
  ast_unary_operator(T&& op, std::unique_ptr<ast_expression> rhs) : _operator(std::move(op)), _rhs(std::move(rhs)) {
    assert(gUNARY_OPERATORS.find(_operator) != gUNARY_OPERATORS.end() && "");
  }

  virtual void print() {
    std::cout << _operator;
    _rhs->print();
  }


  template<typename Visitor, typename = std::enable_if_t<std::is_member_function_pointer_v<decltype(&Visitor::visit)>>>
  typename Visitor::return_type accept(std::unique_ptr<Visitor> visitor) { return visitor->visit(std::make_unique<decltype(this)>(this)); }
};

} // namespace syntax
