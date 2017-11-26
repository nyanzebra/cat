#pragma once

#include "deps/std.hpp"

namespace cat {

class entity_modifiers {
private:
  modifier _modifier;
  std::string _as_string;
protected:
public:
private:
protected:
public:
  entity_modifiers(enum modifier modifier) : _modifier(modifier) {
    _as_string = "";
    if (_modifier & modifier::kEXTERN) {
      _as_string += "extern ";
    }
    if (_modifier & modifier::kSTATIC) {
      _as_string += "static ";
    }
    if (_modifier & modifier::kVOLATILE) {
      _as_string += "volatile ";
    }
    if (_modifier & modifier::kMUTABLE) {
      _as_string += "mutable ";
    }
  }

  const bool is_mutable() const { return _modifier & modifier::kMUTABLE; }
  const bool is_volatile() const { return _modifier & modifier::kVOLATILE; }
  const bool is_extern() const { return _modifier & modifier::kEXTERN; }
  const bool is_static() const { return _modifier & modifier::kSTATIC; }

  std::string as_string() const { return _as_string; }
};

} // namespace cat
