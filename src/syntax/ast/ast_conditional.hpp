#pragma once

#include "ast_expression.hpp"

namespace syntax {

// if, for, while, etc...
class ast_conditional : public ast_expression {
private:
protected:
  std::unique_ptr<ast_expression> _condition, _body;
public:
private:
protected:
public:
  ast_conditional(std::unique_ptr<ast_expression> condition, std::unique_ptr<ast_expression> body) : _condition(std::move(condition)), _body(std::move(body)) {}
};

} // namespace syntax
