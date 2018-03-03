#pragma once

#include "deps/std.hpp"
//
// #include "cat/entity.hpp"

namespace syntax {

enum class access_modifier : unsigned char {
  kPRIVATE, // default
  kPROTECTED,
  kPUBLIC
};

// so in order for this to work we need to be able to import modules...
// so we need a map of modules, since they are *globally* known

enum class symbol : unsigned char {
  kTYPE,
  kFUNCTION,
  kVARIABLE
};



// what I want it to look like scope[kPUBLIC][kTYPE]["MyClass"]["MyType"]
// should return an iterator
// then can see if scope.end() == it for invalid

// have a cache of all symbols
// it has 3 slots, public, protected, and private
// each one of those has a slot (symbol: type, function, variable)
// each one of those can have a string for a name
// that leads to a final value of the scope name
// the scope name is the mangled name given for a variable
// names will be <module>_<interface>_<class>_<function>_<variable>
// a 'hit' counts as long as it matches everything behind the last marker
// e.g. std_testclass std_testclass_testfunction
// so, the testfunction can be found in the testclass
// however, std_testclass std_othertestclass_testfunction
// this shows a function that is inaccessible
class scope {
private:
  std::string _module;
  std::unordered_map<std::string, std::string> _public_symbols;
  std::unordered_map<std::string, std::string> _protected_symbols;
  std::unordered_map<std::string, std::string> _private_symbols;
protected:
public:
private:
protected:
public:
  template<typename T = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  scope(T&& module) : _module(std::move(module)) {}
  template<typename T = scope, typename = std::enable_if_t<std::is_constructible<scope, T>::value>>
  scope(const T& other) { _public_symbols = other._public_symbols; }
  template<typename T = scope, typename = std::enable_if_t<std::is_constructible<scope, T>::value>>
  scope(T&& other) { _public_symbols = std::move(other._public_symbols); }

  template<typename T = scope, typename = std::enable_if_t<std::is_constructible<scope, T>::value>>
  scope& operator=(const T& other) { _public_symbols = other._public_symbols; }
  template<typename T = scope, typename = std::enable_if_t<std::is_constructible<scope, T>::value>>
  scope& operator=(T&& other) { _public_symbols = std::move(other._public_symbols); }

  template<typename T = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  bool has_public_symbol(const T& key) { return _public_symbols.find(key) != _public_symbols.end(); }
  template<typename T = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  bool has_public_symbol(T&& key) { return _public_symbols.find(std::move(key)) != _public_symbols.end(); }
  template<typename T = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  bool get_public_symbol(const T& key) { return _public_symbols.emplace(key) != _public_symbols.end(); }
  template<typename T = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  bool get_public_symbol(T&& key) { return _public_symbols.find(std::move(key)) != _public_symbols.end(); }
  template<typename T = std::string, typename U = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value && std::is_constructible<std::string, U>::value>>
  bool add_public_symbol(const T& key, const U& value) { return _public_symbols.emplace(key, value); }
  template<typename T = std::string, typename U = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value && std::is_constructible<std::string, U>::value>>
  bool add_public_symbol(T&& key, U&& value) { return _public_symbols.emplace(std::move(key), std::move(value)); }

  template<typename T = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  bool has_protected_symbol(const T& key) { return _protected_symbols.find(key) != _protected_symbols.end(); }
  template<typename T = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  bool has_protected_symbol(T&& key) { return _protected_symbols.find(std::move(key)) != _protected_symbols.end(); }
  template<typename T = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  bool get_protected_symbol(const T& key) { return _protected_symbols.emplace(key) != _protected_symbols.end(); }
  template<typename T = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  bool get_protected_symbol(T&& key) { return _protected_symbols.find(std::move(key)) != _protected_symbols.end(); }
  template<typename T = std::string, typename U = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value && std::is_constructible<std::string, U>::value>>
  bool add_protected_symbol(const T& key, const U& value) { return _protected_symbols.emplace(key, value); }
  template<typename T = std::string, typename U = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value && std::is_constructible<std::string, U>::value>>
  bool add_protected_symbol(T&& key, U&& value) { return _protected_symbols.emplace(std::move(key), std::move(value)); }

  template<typename T = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  bool has_private_symbol(const T& key) { return _private_symbols.find(key) != _private_symbols.end(); }
  template<typename T = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  bool has_private_symbol(T&& key) { return _private_symbols.find(std::move(key)) != _private_symbols.end(); }
  template<typename T = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  bool get_private_symbol(const T& key) { return _private_symbols.emplace(key) != _private_symbols.end(); }
  template<typename T = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  bool get_private_symbol(T&& key) { return _private_symbols.find(std::move(key)) != _private_symbols.end(); }
  template<typename T = std::string, typename U = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value && std::is_constructible<std::string, U>::value>>
  bool add_private_symbol(const T& key, const U& value) { return _private_symbols.emplace(key, value); }
  template<typename T = std::string, typename U = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value && std::is_constructible<std::string, U>::value>>
  bool add_private_symbol(T&& key, U&& value) { return _private_symbols.emplace(std::move(key), std::move(value)); }
};

// class scope {
// private:
//   std::unordered_map<std::string, std::pair<scope_instance, cat::type_entity_ptr>> _type_symbols;
//   std::unordered_map<std::string, std::pair<scope_instance, cat::function_entity_ptr>> _function_symbols;
//   std::unordered_map<std::string, std::pair<scope_instance, cat::variable_entity_ptr>> _variable_symbols;
//
//   std::string _module;
// protected:
// public:
// private:
// protected:
// public:
//   template<typename T = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
//   scope(T&& module = "") : scope(std::move(module), {}) {}
//   template<typename T = std::string, typename U = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value && std::is_constructible<scope, U>::value>>
//   scope(T&& module, U&& propogated_scope) : _module(std::move(module)) {
//     _type_symbols.insert(propogated_scope._type_symbols.begin(),propogated_scope._type_symbols.end());
//     _function_symbols.insert(propogated_scope._function_symbols.begin(),propogated_scope._function_symbols.end());
//     _variable_symbols.insert(propogated_scope._variable_symbols.begin(),propogated_scope._variable_symbols.end());
//   }
//
//   template<typename T, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
//   std::pair<scope_instance, cat::type_entity_ptr>& operator[](T&& key) { return _type_symbols[std::move(key)]; }
//   template<typename T, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
//   std::pair<scope_instance, cat::function_entity_ptr>& operator[](T&& key) { return _function_symbols[std::move(key)]; }
//   template<typename T, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
//   std::pair<scope_instance, cat::variable_entity_ptr>& operator[](T&& key) { return _variable_symbols[std::move(key)]; }
//
//   template<typename T, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
//   const std::pair<scope_instance, cat::type_entity_ptr>& operator[](T&& key) const { return _type_symbols[std::move(key)]; }
//   template<typename T, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
//   const std::pair<scope_instance, cat::function_entity_ptr>& operator[](T&& key) const { return _function_symbols[std::move(key)]; }
//   template<typename T, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
//   const std::pair<scope_instance, cat::variable_entity_ptr>& operator[](T&& key) const { return _variable_symbols[std::move(key)]; }
// };
// TODO fix
static const scope gSCOPE = scope("");

gSCOPE.add_public_symbol("auto", "");
gSCOPE.add_public_symbol("bool", "");
gSCOPE.add_public_symbol("char", "");
gSCOPE.add_public_symbol("flt32", "");
gSCOPE.add_public_symbol("flt64", "");
gSCOPE.add_public_symbol("int8", "");
gSCOPE.add_public_symbol("int16", "");
gSCOPE.add_public_symbol("int32", "");
gSCOPE.add_public_symbol("int64", "");
gSCOPE.add_public_symbol("uint8", "");
gSCOPE.add_public_symbol("uint16", "");
gSCOPE.add_public_symbol("uint32", "");
gSCOPE.add_public_symbol("uint64", "");
gSCOPE.add_public_symbol("void", "");

//
// gSCOPE["auto"] = cat::make_auto_type();
// gSCOPE["void"] = cat::make_void_type();
// gSCOPE["bool"] = cat::make_bool_type();
// gSCOPE["char"] = cat::make_char_type();
// gSCOPE["byte"] = cat::make_byte_type();
// gSCOPE["int8"] = cat::make_int8_type();
// gSCOPE["int16"] = cat::make_int16_type();
// gSCOPE["int32"] = cat::make_int32_type();
// gSCOPE["int64"] = cat::make_int64_type();
// gSCOPE["uint8"] = cat::make_uint8_type();
// gSCOPE["uint16"] = cat::make_uint16_type();
// gSCOPE["uint32"] = cat::make_uint32_type();
// gSCOPE["uint64"] = cat::make_uint64_type();
// gSCOPE["flt32"] = cat::make_flt32_type();
// gSCOPE["flt64"] = cat::make_flt64_type();


} // namespace syntax
