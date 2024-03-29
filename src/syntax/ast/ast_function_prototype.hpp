#pragma once

#include "ast_type.hpp"

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
  ast_function_prototype(T&& name, std::unique_ptr<ast_type>&& ret, std::list<std::unique_ptr<ast_type>>&& args) : _name(std::move(name)), _args(std::move(args)), _return(std::move(ret)) {}

  std::ostream& print(std::ostream& stream, size_t tabs = 0) override {
    _return->print(stream);
    stream << " " << _name << "(";
    for (auto it = _args.begin(); it != _args.end(); ++it) {
      (*it)->print(stream);
    }
    stream << ")";
    return stream;
  }

  const std::string& name() const { return _name; }
  template<typename T, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  void name(T&& value) { _name = std::move(value); }
  void name(const std::string& value) { _name = value; }
  const std::list<std::unique_ptr<ast_type>>& args() const { return _args; }
  const std::unique_ptr<ast_type>& result() const { return _return; }


  void* accept(code_generator_visitor* visitor) override;
};

} // namespace syntax
