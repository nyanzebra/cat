#pragma once

#include "ast_expression.hpp"
#include "ast_type.hpp"
#include "modifiers.hpp"

namespace syntax {

// variable TODO: add value
class ast_variable final : public ast_expression {
private:
  std::string _name;
  std::unique_ptr<ast_type> _type;
  modifiers _modifiers;
protected:
public:
private:
protected:
public:
  template<typename T, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  ast_variable(T&& name, std::unique_ptr<ast_type> type, const modifiers modifiers = modifiers::kNONE) : _name(std::move(name)), _type(std::move(type)), _modifiers(modifiers) {}

  const std::string& name() const { return _name; }
  const std::unique_ptr<ast_type>& type() const { return _type; }
  const bool is_mutable() const { return _modifiers & modifiers::kMUTABLE; }
  const bool is_extern() const { return _modifiers & modifiers::kEXTERN; }
  const bool is_static() const { return _modifiers & modifiers::kSTATIC; }
  const bool is_volatile() const { return _modifiers & modifiers::kVOLATILE; }

  void print() override {}

  template<typename Visitor, typename = std::enable_if_t<std::is_member_function_pointer<decltype(&Visitor::visit)>::value>>
  typename Visitor::return_type accept(std::unique_ptr<Visitor> visitor) { return visitor->visit(std::make_unique<decltype(this)>(this)); }
};

} // namespace syntax
