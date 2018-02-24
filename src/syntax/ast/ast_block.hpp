#pragma once

#include "ast_node.hpp"
#include "ast_expression.hpp"

namespace syntax {

class ast_block final : public ast_expression {
private:
  std::list<std::unique_ptr<ast_expression>> _expressions;
public:
  ~ast_block() = default;

  void print(size_t indent) override { //TODO: should be able to pretty print with indent
    std::cout << '{' << std::endl;
    for (auto it = _expressions.begin(); it != _expressions.end(); ++it) {
      (*it)->print(indent + 1);
    }
    std::cout << '}';
  }

  void add_expression(std::unique_ptr<ast_expression> expr) { _expressions.push_back(std::move(expr)); }

  template<typename Visitor, typename = std::enable_if_t<std::is_member_function_pointer<decltype(&Visitor::visit)>::value>>
  typename Visitor::return_type accept(std::unique_ptr<Visitor> visitor) { return visitor->visit(std::make_unique<decltype(this)>(this)); }
};

} // namespace syntax
