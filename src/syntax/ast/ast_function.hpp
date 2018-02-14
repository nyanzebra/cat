#pragma once

#include "ast_function_prototype.hpp"
#include "ast_block.hpp"

namespace syntax {

class ast_function : public ast_expression {
private:
  std::unique_ptr<ast_function_prototype> _prototype;
  std::unique_ptr<ast_block> _body;
protected:
public:
private:
protected:
public:
  ast_function(std::unique_ptr<ast_function_prototype> prototype, std::unique_ptr<ast_block> body) : _prototype(std::move(prototype)), _body(std::move(body)) {}

  void print() override {
    _prototype->print();
    _body->print();
  }

  template<typename Visitor, typename = std::enable_if_t<std::is_member_function_pointer<decltype(&Visitor::visit)>::value>>
  typename Visitor::return_type accept(std::unique_ptr<Visitor> visitor) { return visitor->visit(std::make_unique<decltype(this)>(this)); }
};

} // namespace syntax
