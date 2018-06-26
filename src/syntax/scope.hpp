#pragma once

#include "deps/std.hpp"
#include "deps/llvm.hpp"

namespace syntax {

enum class scope : char {
  kPRIVATE,
  kPROTECTED,
  kPUBLIC
};

class scoped_variable {
private:
  scope _scope;
  llvm::AllocaInst* _value;
protected:
public:
private:
protected:
public:
  scoped_variable(enum scope scope, llvm::AllocaInst* value) : _scope(scope), _value(value) {}

  const scope& scope() const { return _scope; }
  void scope(const enum scope& value) { _scope = value; }
  void scope(enum scope&& value) { _scope = std::move(value); }

  const llvm::AllocaInst* value() const { return _value; }
  void value(llvm::AllocaInst* value) { _value = value; }
};
// map of aliases from a module name to a module i.e. use ... as ...
// or perhaps like rust http://www.suspectsemantics.com/blog/2016/05/26/rust-modules-and-file-hierarchy/

// should have a map of strings that represent valid symbols to their scope (public, protected, private)
// should have a current scope

//symbol name will be of form module-A:module-B:module-...:<class/function>-A:variable-<actual name>
class context {
private:
  static std::unordered_map<std::string, scoped_variable> _symbols;
  static std::unordered_map<std::string, llvm::Type*> _typedefs;
protected:
public:
private:
protected:
public:
  static bool has_symbol(const std::string& key);
  static bool has_symbol(std::string&& key);
  static void remove_symbol(const std::string& key);
  static void remove_symbol(std::string&& key);
  static void add_symbol(const std::string& key, const scoped_variable& value);
  static void add_symbol(std::string&& key, scoped_variable&& value);
  static const scoped_variable& get_symbol(const std::string& key);
  static const scoped_variable& get_symbol(std::string&& key);

  static bool has_typedef(const std::string& key);
  static bool has_typedef(std::string&& key);
  static void remove_typedef(const std::string& key);
  static void remove_typedef(std::string&& key);
  static void add_typedef(const std::string& key, llvm::Type* value);
  static void add_typedef(std::string&& key, llvm::Type* value);
  static llvm::Type* get_typedef(const std::string& key);
  static llvm::Type* get_typedef(std::string&& key);
};

} // namespace syntax
