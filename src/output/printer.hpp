#pragma once

#include "styler.hpp"
#include "formatter.hpp"

#include "deps/std.hpp"

namespace output {

enum class output_type : unsigned char {
  kSTANDARD_OUTPUT,
  kSTANDARD_ERROR,
  kFILE,
  kNULL,
};

class printer {
private:
  output_type _type;
  std::ofstream _file;

  styler _styler;
  formatter _formatter;

  template<typename T = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  void _print(const T& message) const {
    switch (_type) {
      case output_type::kSTANDARD_OUTPUT:
        {

          std::cout << message << std::endl;
        }
        break;
      case output_type::kSTANDARD_ERROR:
        std::cerr << message << std::endl;
        break;
      case output_type::kFILE:
        //_file << message << std::endl;
        break;
      case output_type::kNULL:
      default:
        break;
    }
  }

  template<typename T = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  void _print(T&& message) const {
    switch (_type) {
      case output_type::kSTANDARD_OUTPUT:
        {

          std::cout << std::move(message) << std::endl;
        }
        break;
      case output_type::kSTANDARD_ERROR:
        std::cerr << std::move(message) << std::endl;
        break;
      case output_type::kFILE:
        //_file << std::move(message) << std::endl;
        break;
      case output_type::kNULL:
      default:
        break;
    }
  }
protected:
public:
private:
protected:
public:
  printer() : printer(output_type::kNULL) {}
  printer(output_type type) : _type(type), _file("log.txt") {}

  const styler& styler() const { return _styler; }
  const formatter& formatter() const { return _formatter; }

  template<typename T = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  void print(T&& message) const { _print(_styler.style(std::move(message))); }

  template<typename T = std::string, typename... Args, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  void print(T&& message, Args&&... args) const { _print(_styler.style(std::move(message))); print(std::move(args)...); }
}; // class printer

} // namespace output
