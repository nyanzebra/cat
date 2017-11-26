#pragma once

#include "ast_expression.hpp"
#include "modifiers.hpp"

namespace syntax {

  // variable
  class ast_variable : public ast_expression {
  private:
    std::string _name, _type;
    modifiers _modifiers;
  protected:
  public:
  private:
  protected:
  public:
    template<typename T, typename U, typename = std::enable_if_t<std::is_constructible_v<std::string, T> && std::is_constructible_v<std::string, U>>>
    ast_variable(T&& name, U&& type, const modifiers modifiers = modifiers::kNONE) : _name(std::move(name)), _type(std::move(type)), _modifiers(modifiers) {}

    const std::string& name() const { return _name; }
    const std::string& type() const { return _type; }
    const bool is_mutable() const { return static_cast<size_t>(_modifiers) & static_cast<size_t>(modifiers::kMUTABLE); }
    const bool is_extern() const { return static_cast<size_t>(_modifiers) & static_cast<size_t>(modifiers::kEXTERN); }
    const bool is_static() const { return static_cast<size_t>(_modifiers) & static_cast<size_t>(modifiers::kSTATIC); }
    const bool is_volatile() const { return static_cast<size_t>(_modifiers) & static_cast<size_t>(modifiers::kVOLATILE); }


    template<typename Visitor, typename = std::enable_if_t<std::is_member_function_pointer_v<decltype(&Visitor::visit)>>>
    typename Visitor::return_type accept(std::unique_ptr<Visitor> visitor) { return visitor->visit(std::make_unique<decltype(this)>(this)); }
  };

} // namespace syntax
