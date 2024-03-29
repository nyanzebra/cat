#pragma once

#include "ast_expression.hpp"
#include "modifiers.hpp"

#include "deps/std.hpp"

namespace syntax {
//, typename = std::enable_if_t<std::is_arithmetic<T>::value>
template <typename T>
class ast_arithmetic final : public ast_expression {
private:
  T _value;
protected:
public:
private:
protected:
public:
  template<typename U = T, typename = std::enable_if_t<std::is_constructible<T, U>::value>>
  ast_arithmetic(const U& value) : _value(value) {}
  template<typename U = T, typename = std::enable_if_t<std::is_constructible<T, U>::value>>
  ast_arithmetic(U&& value) : _value(std::move(value)) {}
  virtual ~ast_arithmetic() = default;

  friend bool operator==(const ast_arithmetic& lhs, const ast_arithmetic& rhs) {
    if (&lhs == &rhs) return true;
    if (lhs._value == rhs._value) return true;
    return false;
  }

  friend bool operator==(ast_arithmetic&& lhs, ast_arithmetic&& rhs) {
    if (&lhs == &rhs) return true;
    if (lhs._value == rhs._value) return true;
    return false;
  }

  operator T() { return _value; }
  operator T() const { return _value; }

  std::ostream& print(std::ostream& stream, size_t tabs = 0) override {
    indent(stream, tabs);
    std::is_same<T, bool>::value ? (stream << std::boolalpha << _value << std::dec) : (stream << _value);
    return stream;
  }

  const T& value() const { return _value; }
  void value(const T& value) { _value = value; }
  template<typename U = T, typename = std::enable_if_t<std::is_constructible<T, U>::value>>
  void value(U&& value) { _value = std::move(value); }

  void* accept(code_generator_visitor* visitor) override;
};

typedef ast_arithmetic<bool> ast_bool;
typedef ast_arithmetic<signed char> ast_char;
typedef ast_char ast_int8;
typedef ast_arithmetic<unsigned char> ast_uchar;
typedef ast_uchar ast_uint8;
typedef ast_arithmetic<signed short> ast_int16;
typedef ast_arithmetic<unsigned short> ast_uint16;
typedef ast_arithmetic<signed long> ast_int32;
typedef ast_arithmetic<unsigned long> ast_uint32;
typedef ast_arithmetic<signed long long> ast_int64;
typedef ast_arithmetic<unsigned long long> ast_uint64;
typedef ast_arithmetic<float> ast_flt32;
typedef ast_arithmetic<double> ast_flt64;

} // namespace syntax
