#pragma once

#include "ast_expression.hpp"

namespace syntax {

class ast_function_call : public ast_expression {
private:
  std::string _callee;
  std::vector<std::unique_ptr<ast_expression>> _args;
protected:
public:
private:
protected:
public:
  template<typename T, typename = std::enable_if_t<std::is_constructible_v<std::string, T>>>
  ast_function_call(T&& callee, std::vector<std::unique_ptr<ast_expression>>&& args) : _callee(std::move(callee)), _args(std::move(args)) {

  }

  virtual void print() {
    std::cout << _callee << "(";
    // for (auto arg : _args) {
    //   std::cout << arg->print();
    // }
    std::cout << ")";
  }

  template<typename Visitor, typename = std::enable_if_t<std::is_member_function_pointer_v<decltype(&Visitor::visit)>>>
  typename Visitor::return_type accept(std::unique_ptr<Visitor> visitor) { return visitor->visit(std::make_unique<decltype(this)>(this)); }
};

} // namespace syntax
