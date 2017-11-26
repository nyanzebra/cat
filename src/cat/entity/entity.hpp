#pragma once

#include "cat/modifier.hpp"
#include "cat/type.hpp"

#include "entity_modifiers.hpp"

#include "deps/std.hpp"

namespace cat {

class entity {
private:
protected:
  std::string _name;
  std::string _global_name;
  type _type;
  entity_modifiers _entity_modifiers;
  std::unique_ptr<entity> _pointer;
  std::unique_ptr<entity> _reference;

public:
private:
protected:
  type abstraction_type() const {
    if (_type == type::kPOINTER && _pointer != nullptr) {
      return _pointer->type();
    }
    if (_type == type::kREFERENCE && _reference != nullptr) {
      return _reference->type();
    }
    return type::kNONE;//TODO: fix type
  }

  bool is_integer() {
    switch (_type) {
    case type::kBOOL:
    case type::kCHAR:
    case type::kBYTE:
    case type::kINT8:
    case type::kINT16:
    case type::kINT32:
    case type::kINT64:
    case type::kUINT8:
    case type::kUINT16:
    case type::kUINT32:
    case type::kUINT64:
      return true;
    default:
      return false;
    }
  }

  bool is_float() {
    switch (_type) {
    case type::kFLT32:
    case type::kFLT64:
      return true;
    default:
      return false;
    }
  }

  bool is_number() { return is_float() || is_integer(); }

  bool is_pointer() { return _type == type::kPOINTER; }
  bool is_reference() { return _type == type::kREFERENCE; }
  bool is_auto() { return (_type == type::kAUTO || (abstraction_type() == type::kAUTO)); }

  bool is_static() const { return _entity_modifiers.is_static(); }
  bool is_extern() const { return _entity_modifiers.is_extern(); }
  bool is_mutable() const { return _entity_modifiers.is_mutable(); }
  bool is_volatile() const { return _entity_modifiers.is_volatile(); }
public:
  template<typename T = std::string, typename U = std::string, typename = std::enable_if_t<std::is_constructible_v<std::string, T> && std::is_constructible_v<std::string, U>>>
  entity(T&& name, U&& global_name, const enum type type) : entity(std::forward<T>(name), std::forward<U>(global_name), type, entity_modifiers(modifier::kNONE)) {}
  template<typename T = std::string, typename U = std::string, typename = std::enable_if_t<std::is_constructible_v<std::string, T> && std::is_constructible_v<std::string, U>>>
  entity(T&& name, U&& global_name, const enum type type, const entity_modifiers modifiers) : _name(std::move(name)), _global_name(std::move(global_name)), _type(type), _entity_modifiers(modifiers) {}
  virtual ~entity() = default;

  std::string global_name() const { return _global_name; }
  std::string name() const { return _name; }
  type type() const { return _type; }
  virtual size_t size() const {
    switch (_type) {
    case type::kNULLPTR:
      return sizeof(nullptr);
    case type::kPOINTER:
    case type::kREFERENCE:
      return sizeof(void*);
    case type::kAUTO:
      //return sizeof(auto); TODO: need to have real size
    case type::kPATTERN:
    default:
      assert(false && "Cannot know size of unknown type...");
      return 0;
    }
  }
};

typedef std::unique_ptr<entity> entity_ptr;
typedef std::list<entity_ptr> entity_ptrs;

} // namespace cat
