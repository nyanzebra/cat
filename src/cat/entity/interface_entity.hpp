#pragma once

#include "deps/std.hpp"

#include "entity.hpp"

namespace cat {

class interface_entity : public type_entity {
private:
  size_t _size;
protected:
public:
private:
protected:
public:

  size_t size() const { assert(_type == type::kINTERFACE && "Size of interface can only work on interfaces"); return _size; }
};

} // namespace cat
