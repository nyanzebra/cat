#pragma once

#include "deps/std.hpp"

#include "type_entity.hpp"

namespace cat {

class class_entity : public type_entity {
private:
  size_t _size;
protected:
public:
private:
protected:
public:

  size_t size() const {
    // assert(_type == type::kCLASS && "Size of class can only work on classes"); 
    return _size;
  }
};

} // namespace cat
