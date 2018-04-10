#pragma once

#include "deps/std.hpp"

namespace syntax {

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
  scope(const scope& other) { _public_symbols = other._public_symbols; }
  scope(scope&& other) { _public_symbols = std::move(other._public_symbols); }

  scope& operator=(const scope& other) { _public_symbols = other._public_symbols; return *this; }
  scope& operator=(scope&& other) { _public_symbols = std::move(other._public_symbols); return *this; }

  template<typename T = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  bool has_public_symbol(const T& key) { return _public_symbols.find(key) != _public_symbols.end(); }
  template<typename T = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  bool has_public_symbol(T&& key) { return _public_symbols.find(std::move(key)) != _public_symbols.end(); }
  template<typename T = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  void remove_public_symbol(const T& key) { return _public_symbols.erase(key); }
  template<typename T = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  void remove_public_symbol(T&& key) { return _public_symbols.erase(std::move(key)); }
  template<typename T = std::string, typename U = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value && std::is_constructible<std::string, U>::value>>
  void add_public_symbol(const T& key, const U& value) { _public_symbols.emplace(key, value); }
  template<typename T = std::string, typename U = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value && std::is_constructible<std::string, U>::value>>
  void add_public_symbol(T&& key, U&& value) { _public_symbols.emplace(std::move(key), std::move(value)); }

  template<typename T = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  bool has_protected_symbol(const T& key) { return _protected_symbols.find(key) != _protected_symbols.end(); }
  template<typename T = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  bool has_protected_symbol(T&& key) { return _protected_symbols.find(std::move(key)) != _protected_symbols.end(); }
  template<typename T = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  void remove_protected_symbol(const T& key) { return _protected_symbols.erase(key); }
  template<typename T = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  void remove_protected_symbol(T&& key) { return _protected_symbols.erase(std::move(key)); }
  template<typename T = std::string, typename U = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value && std::is_constructible<std::string, U>::value>>
  void add_protected_symbol(const T& key, const U& value) { _protected_symbols.emplace(key, value); }
  template<typename T = std::string, typename U = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value && std::is_constructible<std::string, U>::value>>
  void add_protected_symbol(T&& key, U&& value) { _protected_symbols.emplace(std::move(key), std::move(value)); }

  template<typename T = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  bool has_private_symbol(const T& key) { return _private_symbols.find(key) != _private_symbols.end(); }
  template<typename T = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  bool has_private_symbol(T&& key) { return _private_symbols.find(std::move(key)) != _private_symbols.end(); }
  template<typename T = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  void remove_private_symbol(const T& key) { return _private_symbols.erase(key); }
  template<typename T = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  void remove_private_symbol(T&& key) { return _private_symbols.erase(std::move(key)); }
  template<typename T = std::string, typename U = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value && std::is_constructible<std::string, U>::value>>
  void add_private_symbol(const T& key, const U& value) { _private_symbols.emplace(key, value); }
  template<typename T = std::string, typename U = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value && std::is_constructible<std::string, U>::value>>
  void add_private_symbol(T&& key, U&& value) { _private_symbols.emplace(std::move(key), std::move(value)); }
};

} // namespace syntax
