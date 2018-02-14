#pragma once

#include "ast_expression.hpp"

namespace syntax {

class ast_function_prototype : public ast_expression {
private:
  std::string _name;
  std::list<std::unique_ptr<ast_type>> _args;
  std::unique_ptr<ast_type> _return;
protected:
public:
private:
protected:
public:
  template<typename T, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  ast_function_prototype(T&& name, std::unique_ptr<ast_type>&& ret, std::list<std::unique_ptr<ast_type>>&& args) : _name(std::move(name)), _return(std::move(ret)), _args(std::move(args)) {}

  void print() override {
    std::cout << _name << "(";
    for (auto it = _args.begin(); it != _args.end(); ++it) {
      (*it)->print();
    }
    std::cout << ")";
  }

  const std::string& name() const { return _name; }
  const std::list<std::unique_ptr<ast_type>>& args() const { return _args; }

  template<typename Visitor, typename = std::enable_if_t<std::is_member_function_pointer<decltype(&Visitor::visit)>::value>>
  typename Visitor::return_type accept(std::unique_ptr<Visitor> visitor) { return visitor->visit(std::make_unique<decltype(this)>(this)); }
};

} // namespace syntax
