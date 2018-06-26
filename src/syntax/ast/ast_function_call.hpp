#pragma once

#include "ast_expression.hpp"

namespace syntax {

class ast_function_call final : public ast_expression {
private:
  std::string _callee;
  std::list<std::unique_ptr<ast_expression>> _args;
protected:
public:
private:
protected:
public:
  template<typename T, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  ast_function_call(T&& callee, std::list<std::unique_ptr<ast_expression>>&& args) : _callee(std::move(callee)), _args(std::move(args)) {}

  std::ostream& print(std::ostream& stream, size_t tabs = 0) override {
    stream << _callee << "(";
    for (auto it = _args.begin(); it != _args.end(); ++it) {
      (*it)->print(stream);
    }
    stream << ")";
    return stream;
  }

  const std::string& callee() const { return _callee; }
  const std::list<std::unique_ptr<ast_expression>>& args() const { return _args; }


  void* accept(code_generator_visitor* visitor) override;
};

} // namespace syntax
