#include "scope.hpp"

namespace syntax {

std::unordered_map<std::string, scoped_variable> context::_symbols;
std::unordered_map<std::string, llvm::Type*> context::_typedefs;

bool context::has_symbol(const std::string& key) { return _symbols.find(key) != _symbols.end(); }
bool context::has_symbol(std::string&& key) { return _symbols.find(std::move(key)) != _symbols.end(); }
void context::remove_symbol(const std::string& key) { _symbols.erase(key); }
void context::remove_symbol(std::string&& key) { _symbols.erase(std::move(key)); }
void context::add_symbol(const std::string& key, const scoped_variable& value) { _symbols.emplace(key, value); }
void context::add_symbol(std::string&& key, scoped_variable&& value) { _symbols.emplace(std::move(key), std::move(value)); }
const scoped_variable& context::get_symbol(const std::string& key) { return _symbols.at(key); }
const scoped_variable& context::get_symbol(std::string&& key) { return _symbols.at(std::move(key)); }

bool context::has_typedef(const std::string& key) { return _typedefs.find(key) != _typedefs.end(); }
bool context::has_typedef(std::string&& key) { return _typedefs.find(std::move(key)) != _typedefs.end(); }
void context::remove_typedef(const std::string& key) { _typedefs.erase(key); }
void context::remove_typedef(std::string&& key) { _typedefs.erase(std::move(key)); }
void context::add_typedef(const std::string& key, llvm::Type* value) { _typedefs.emplace(key, value); }
void context::add_typedef(std::string&& key, llvm::Type* value) { _typedefs.emplace(std::move(key), value); }
llvm::Type* context::get_typedef(const std::string& key) { return _typedefs.at(key); }
llvm::Type* context::get_typedef(std::string&& key) { return _typedefs.at(std::move(key)); }

}
