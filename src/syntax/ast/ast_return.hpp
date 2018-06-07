#pragma once

#include "ast_expression.hpp"

namespace syntax {

class ast_return final : public ast_expression {
private:
  std::unique_ptr<ast_expression> _expression;
public:
  ast_return(std::unique_ptr<ast_expression> expr) : _expression(std::move(expr)) {}
  virtual ~ast_return() = default;

  std::ostream& print(std::ostream& stream, size_t tabs = 0) override { //TODO: should be able to pretty print with indent
    indent(stream, tabs);
    stream << "return ";
    _expression->print(stream);
    return stream;
  }

  const std::unique_ptr<ast_expression>& expression() const { return _expression; }

  void* accept(code_generator_visitor* visitor, const scope& current_scope) override;
};

} // namespace syntax
