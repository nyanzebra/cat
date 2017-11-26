#pragma once

#include "deps/std.hpp"

#include "entity.hpp"
#include "function_signature.hpp"

namespace cat {

class function_entity : public entity {
private:
  function_signature _signature;
  entity_ptrs _args_types;
protected:
public:
private:
protected:
public:
  function_entity() = default;
  function_entity(entity_ptr return_type, entity_ptrs&& args_types, std::string&& name, std::string&& global_name, const enum type type) : _signature(std::move(return_type), std::move(args_types)), entity(std::forward<std::string>(name), std::forward<std::string>(global_name), type) {

  }
  ~function_entity() = default;

  const function_signature& function_signature() const { return _signature; }
  const entity_ptrs& args_types() const { return _args_types; }
  size_t size() const { assert(_type == type::kFUNCTION && "Size of function can only work on functions"); return sizeof(void*); }
};

typedef std::unique_ptr<function_entity> function_entity_ptr;
typedef std::list<function_entity_ptr> function_entity_ptrs;

} // namespace cat
