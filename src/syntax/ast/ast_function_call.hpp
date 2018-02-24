#pragma once

#include "ast_expression.hpp"

namespace syntax {

class ast_function_call final : public ast_expression {
private:
  std::string _callee;
  std::vector<std::unique_ptr<ast_expression>> _args;
protected:
public:
private:
protected:
public:
  template<typename T, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  ast_function_call(T&& callee, std::vector<std::unique_ptr<ast_expression>>&& args) : _callee(std::move(callee)), _args(std::move(args)) {}

  std::ostream& print(std::ostream& stream, size_t tabs = 0) override {
    stream << _callee << "(";
    for (auto it = _args.begin(); it != _args.end(); ++it) {
      (*it)->print(stream);
    }
    stream << ")";
    return stream;
  }

  template<typename Visitor, typename = std::enable_if_t<std::is_member_function_pointer<decltype(&Visitor::visit)>::value>>
  typename Visitor::return_type accept(std::unique_ptr<Visitor> visitor) { return visitor->visit(std::make_unique<decltype(this)>(this)); }
};

} // namespace syntax
