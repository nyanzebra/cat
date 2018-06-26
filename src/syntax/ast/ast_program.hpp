#pragma once

#include "ast_expression.hpp"

namespace syntax {

class ast_program : public ast_node {
private:
    std::list<std::unique_ptr<ast_expression>> _expressions;
protected:
public:
private:
protected:
public:
  const std::list<std::unique_ptr<ast_expression>>& expressions() const { return _expressions; }

  void add_expression(std::unique_ptr<ast_expression> expr) { _expressions.push_back(std::move(expr)); }

  std::ostream& print(std::ostream& stream, size_t tabs = 0) override {
    std::cout << "items: " << _expressions.size() << std::endl;
    for (auto it = _expressions.begin(); it != _expressions.end(); ++it) {
      (*it)->print(stream, tabs + 1);
    }
    return stream;
  }

  void* accept(code_generator_visitor* visitor) override;
}; // contains compilation nodes

} // namespace syntax
