#pragma once

#include "deps/std.hpp"

#include "entity.hpp"
#include "function_signature.hpp"

namespace cat {

class type_entity : public entity {
private:
protected:
public:
private:
protected:
public:
  type_entity() = default;
  template<typename T, typename = std::enable_if_t<std::is_constructible_v<std::string, T>>>
  type_entity(T&& name, const enum type type) : type_entity(std::forward<T>(name), std::forward<T>(name), type) {}
  template<typename T, typename U, typename = std::enable_if_t<std::is_constructible_v<std::string, T> && std::is_constructible_v<std::string, U>>>
  type_entity(T&& name, U&& global_name, const enum type type) : entity(std::forward<T>(name), std::forward<T>(global_name), type) {}
  type_entity(const function_signature& signature) : type_entity(signature.as_string(), signature.as_string(), type::kFUNCTION) {}
  virtual ~type_entity() = default;

  size_t size() const {
    switch (_type) {
    case type::kVOID:
      return 0u;
    case type::kBOOL:
      return sizeof(bool);
    case type::kCHAR:
    case type::kBYTE:
    case type::kINT8:
      return sizeof(char);
    case type::kINT16:
      return sizeof(short);
    case type::kINT32:
      return sizeof(int);
    case type::kINT64:
      return sizeof(long long);
    case type::kUINT8:
      return sizeof(unsigned char);
    case type::kUINT16:
      return sizeof(unsigned short);
    case type::kUINT32:
      return sizeof(unsigned int);
    case type::kUINT64:
      return sizeof(unsigned long long);
    case type::kFLT32:
      return sizeof(float);
    case type::kFLT64:
      return sizeof(double);
    default:
      assert(false && "Cannot know size of unknown type...");
      return 0;
    }
  }
};

typedef std::unique_ptr<type_entity> type_entity_ptr;
typedef std::list<type_entity_ptr> type_entity_ptrs;

} // namespace cat
