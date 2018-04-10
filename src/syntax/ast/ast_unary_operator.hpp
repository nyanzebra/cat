#pragma once

#include "ast_expression.hpp"

namespace syntax {

class ast_unary_operator final : public ast_expression {
private:
  std::string _operator;
  std::unique_ptr<ast_expression> _rhs;
protected:
public:
private:
protected:
public:
  template<typename T, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  ast_unary_operator(T&& op, std::unique_ptr<ast_expression> rhs) : _operator(std::move(op)), _rhs(std::move(rhs)) {
    // assert(gUNARY_OPERATORS.find(_operator) != gUNARY_OPERATORS.end() && "");
  }

  std::ostream& print(std::ostream& stream, size_t tabs = 0) override {
    stream << _operator;
    _rhs->print(stream);
    return stream;
  }

  void* accept(code_generator_visitor* visitor, const scope& current_scope) override;
};

} // namespace syntax
