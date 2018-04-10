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

  std::ostream& print(std::ostream& stream, size_t tabs = 0) override {
    if (_condition) {
      stream << "if (";
      _condition->print(stream);
      stream << ")";
      if (_body) {
        stream << ' ';
        _body->print(stream, tabs);
        if (_else) {
          stream << " else ";
          _else->print(stream, tabs);
        }
      } else {
        stream << ";" << std::endl;
      }
    }
    return stream;
  }

  const std::unique_ptr<ast_expression>& other() const { return _else; }

  void* accept(code_generator_visitor* visitor, const scope& current_scope) override;
};

} // namespace syntax
