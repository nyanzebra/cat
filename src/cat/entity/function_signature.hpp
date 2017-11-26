#pragma once

#include "deps/std.hpp"

#include "entity.hpp"

namespace cat {

class function_signature {
private:
  entity_ptr _return_type;
  entity_ptrs _args_types;
  std::string _signature;
protected:
public:
private:
protected:
public:
  function_signature() = default;
  function_signature(entity_ptr return_type, entity_ptrs&& args_types) : _return_type(std::move(return_type)), _args_types(std::move(args_types)) {
    _signature = return_type->name();
    _signature += '(';

    bool comma = false;
    for (auto&& arg : _args_types) {
      if (comma) {
        _signature += ',';
      } else {
        comma = true;
      }
      _signature += arg->name();
    }

    _signature += ')';
  }
  ~function_signature() = default;

  friend bool operator==(const function_signature& lhs, const function_signature& rhs) {
    if (lhs.return_type() != rhs.return_type()) {
      return false;
    }

    if (lhs.args_types().size() != rhs.args_types().size()) {
      return false;
    }

    auto lhs_begin = lhs.args_types().begin();
    auto rhs_begin = rhs.args_types().begin();

    auto lhs_end = lhs.args_types().end();
    auto rhs_end = rhs.args_types().end();

    while (lhs_begin != lhs_end && rhs_begin != rhs_end) {
      if (*(lhs_begin++) != *(rhs_begin++)) {
        return false;
      }
    }

    return true;
  }
  friend bool operator!=(const function_signature& lhs, const function_signature& rhs) { return !(lhs == rhs); }

  std::string as_string() const { return _signature; }
  const entity_ptr& return_type() const { return _return_type; }
  const entity_ptrs& args_types() const { return _args_types; }
};

} // namespace cat
