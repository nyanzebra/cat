#pragma once

#include "ast_conditional.hpp"

namespace syntax {

class ast_if final : public ast_conditional {
private:
  std::unique_ptr<ast_expression> _else;
protected:
public:
private:
protected:
public:
  ast_if(std::unique_ptr<ast_expression> condition, std::unique_ptr<ast_expression> body, std::unique_ptr<ast_expression> other) : ast_conditional(std::move(condition), std::move(body)), _else(std::move(other)) {}

  void print() override {
    std::cout << "if (";
    _condition->print();
    std::cout << ")";
    _body->print();
    if (_else) {
      std::cout << "else";
      _else->print();
    }
  }

  template<typename Visitor, typename = std::enable_if_t<std::is_member_function_pointer<decltype(&Visitor::visit)>::value>>
  typename Visitor::return_type accept(std::unique_ptr<Visitor> visitor) { return visitor->visit(std::make_unique<decltype(this)>(this)); }
};

} // namespace syntax