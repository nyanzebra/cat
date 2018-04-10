#pragma once

#include "ast_expression.hpp"
#include "modifiers.hpp"

#include "utility/enum.hpp"

#include "deps/std.hpp"

namespace syntax {

class ast_type final : public ast_expression {
private:
  std::string _name;
  modifiers _modifiers;
protected:
public:
private:
  void append_mods() {
    if (_modifiers & modifiers::kVOLATILE) {
      _name.insert(0, std::string("volatile "));
    }
    if (_modifiers & modifiers::kMUTABLE) {
      _name.insert(0, std::string("mutable "));
    }
    if (_modifiers & modifiers::kSTATIC) {
      _name.insert(0, std::string("static "));
    }
    if (_modifiers & modifiers::kEXTERN) {
      _name.insert(0, std::string("extern "));
    }
  }
protected:
public:
  ast_type(const std::string& name, const modifiers mods) : _name(name), _modifiers(mods) { append_mods(); }
  template<typename U = std::string, typename = std::enable_if_t<std::is_constructible<std::string, U>::value>>
  ast_type(U&& name, const modifiers mods) : _name(std::move(name)), _modifiers(mods) { append_mods(); }
  virtual ~ast_type() = default;

  friend bool operator==(const ast_type& lhs, const ast_type& rhs) {
    if (&lhs == &rhs) return true;
    if (lhs._name == rhs._name && lhs._modifiers == rhs._modifiers) return true;
    return false;
  }

  friend bool operator==(ast_type&& lhs, ast_type&& rhs) {
    if (&lhs == &rhs) return true;
    if (lhs._name == rhs._name && lhs._modifiers == rhs._modifiers) return true;
    return false;
  }

  operator std::string() { return _name; }
  operator std::string() const { return _name; }

  std::ostream& print(std::ostream& stream, size_t tabs = 0) override {
    indent(stream, tabs);
    stream << _name;
    return stream;
  }

  const std::string& name() const { return _name; }
  void name(const std::string& name) { _name = name; }
  template<typename U = std::string, typename = std::enable_if_t<std::is_constructible<std::string, U>::value>>
  void name(U&& name) { _name = std::move(name); }

  const enum modifiers& modifiers() const { return _modifiers; }
  void modifiers(const enum modifiers& mods) { _modifiers = mods; }
  template<typename U = enum modifiers, typename = std::enable_if_t<std::is_convertible<U, enum modifiers>::value>>
  void modifiers(U&& mods) { _modifiers = std::move(mods); }

  void* accept(code_generator_visitor* visitor, const scope& current_scope) override;
};

} // namespace syntax
