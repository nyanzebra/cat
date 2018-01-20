#pragma once

#include "deps/std.hpp"

#include "entity.hpp"

namespace cat {

class variable_entity : public entity {
private:
protected:
public:
private:
protected:
public:
  variable_entity() = default;
  template<typename T, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  variable_entity(T&& name, const enum type type) : variable_entity(std::forward<T>(name), std::forward<T>(name), type) {}
  template<typename T, typename U, typename = std::enable_if_t<std::is_constructible<std::string, T>::value && std::is_constructible<std::string, U>::value>>
  variable_entity(T&& name, U&& global_name, const enum type type) : entity(std::forward<T>(name), std::forward<T>(global_name), type) {}
  virtual ~variable_entity() = default;
};

typedef std::unique_ptr<variable_entity> variable_entity_ptr;
typedef std::list<variable_entity_ptr> variable_entity_ptrs;

} // namespace cat
