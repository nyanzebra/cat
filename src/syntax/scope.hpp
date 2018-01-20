#pragma once

#include "deps/std.hpp"

#include "cat/entity.hpp"

namespace syntax {

enum scope_instance {
  kPRIVATE, // default
  kPROTECTED,
  kPUBLIC
};

class scope {
private:
  std::unordered_map<std::string, std::pair<scope_instance, cat::type_entity_ptr>> _type_symbols;
  std::unordered_map<std::string, std::pair<scope_instance, cat::function_entity_ptr>> _function_symbols;
  std::unordered_map<std::string, std::pair<scope_instance, cat::variable_entity_ptr>> _variable_symbols;

  std::string _module;
protected:
public:
private:
protected:
public:
  template<typename T = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  scope(T&& module = "") : scope(std::move(module), {}) {}
  template<typename T = std::string, typename U = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value && std::is_constructible<scope, U>::value>>
  scope(T&& module, U&& propogated_scope) : _module(std::move(module)) {
    _type_symbols.insert(propogated_scope._type_symbols.begin(),propogated_scope._type_symbols.end());
    _function_symbols.insert(propogated_scope._function_symbols.begin(),propogated_scope._function_symbols.end());
    _variable_symbols.insert(propogated_scope._variable_symbols.begin(),propogated_scope._variable_symbols.end());
  }

  template<typename T, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  std::pair<scope_instance, cat::type_entity_ptr>& operator[](T&& key) { return _type_symbols[std::move(key)]; }
  template<typename T, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  std::pair<scope_instance, cat::function_entity_ptr>& operator[](T&& key) { return _function_symbols[std::move(key)]; }
  template<typename T, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  std::pair<scope_instance, cat::variable_entity_ptr>& operator[](T&& key) { return _variable_symbols[std::move(key)]; }

  template<typename T, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  const std::pair<scope_instance, cat::type_entity_ptr>& operator[](T&& key) const { return _type_symbols[std::move(key)]; }
  template<typename T, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  const std::pair<scope_instance, cat::function_entity_ptr>& operator[](T&& key) const { return _function_symbols[std::move(key)]; }
  template<typename T, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  const std::pair<scope_instance, cat::variable_entity_ptr>& operator[](T&& key) const { return _variable_symbols[std::move(key)]; }
};
// TODO fix
// static const scope gSCOPE;
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
