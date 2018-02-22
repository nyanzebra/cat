#pragma once

#include "ast_conditional.hpp"

namespace syntax {

class ast_for final : public ast_conditional {
private:
  std::unique_ptr<ast_expression> _start, _end;
protected:
public:
private:
protected:
public:
  ast_for(std::unique_ptr<ast_expression> start, std::unique_ptr<ast_expression> condition, std::unique_ptr<ast_expression> end, std::unique_ptr<ast_expression> then) : ast_conditional(std::move(condition), std::move(then)), _start(std::move(start)), _end(std::move(end)) {}

  void print(size_t tabs) override {
    indent(tabs);
    std::cout << "for (";
    _start->print(0);
    std::cout << "; ";
    _condition->print(0);
    std::cout << "; ";
    _end->print(0);
    std::cout << ")";
    _body->print(tabs);
  }

  template<typename Visitor, typename = std::enable_if_t<std::is_member_function_pointer<decltype(&Visitor::visit)>::value>>
  typename Visitor::return_type accept(std::unique_ptr<Visitor> visitor) { return visitor->visit(std::make_unique<decltype(this)>(this)); }
};

} // namespace syntax
