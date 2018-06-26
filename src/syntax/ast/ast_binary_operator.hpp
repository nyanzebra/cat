#pragma once

#include "ast_expression.hpp"

namespace syntax {

class ast_binary_operator final : public ast_expression {
private:
  std::string _operator;
  std::unique_ptr<ast_expression> _lhs, _rhs;
protected:
public:
private:
protected:
public:
  template<typename T, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  ast_binary_operator(T&& op, std::unique_ptr<ast_expression> lhs, std::unique_ptr<ast_expression> rhs) : _operator(std::move(op)), _lhs(std::move(lhs)), _rhs(std::move(rhs)) {}

  std::ostream& print(std::ostream& stream, size_t tabs = 0) override {
    _lhs->print(stream, tabs);
    stream << " " << _operator << " ";
    _rhs->print(stream);
    return stream;
  }

  void* accept(code_generator_visitor* visitor) override;
};

} // namespace syntax
