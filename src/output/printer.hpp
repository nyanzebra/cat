#pragma once

#include "styler.hpp"
#include "formatter.hpp"

#include "deps/std.hpp"

namespace output {

enum class output_type : unsigned char {
  kSTRING,
  kSTANDARD_OUTPUT,
  kSTANDARD_ERROR,
  kFILE,
  kNULL,
};

class printer {
private:
  output_type _type;
  std::ofstream _file;
  std::stringstream _stream;
  styler _styler;
  formatter _formatter;

  template<typename T>
  void _print(const T& message) const {
    switch (_type) {
      case output_type::kSTRING:
        //_stream << message;
        break;
      case output_type::kSTANDARD_OUTPUT:
        std::cout << message;
        break;
      case output_type::kSTANDARD_ERROR:
        std::cerr << message;
        break;
      case output_type::kFILE:
        //_file << message;
        break;
      case output_type::kNULL:
      default:
      break;
    }
  }

  template<typename T>
  void _print(T&& message) const {
    switch (_type) {
      case output_type::kSTRING:
        //_stream << std::move(message);
        break;
      case output_type::kSTANDARD_OUTPUT:
        std::cout << std::move(message);
        break;
      case output_type::kSTANDARD_ERROR:
        std::cerr << std::move(message);
        break;
      case output_type::kFILE:
        //_file << std::move(message);
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

  const std::string stream() const { return _stream.str(); }
  void reset_stream() { _stream.str(""); }

  const styler& styler() const { return _styler; }
  void styler(const class styler& styler) { _styler = styler; }
  const formatter& formatter() const { return _formatter; }
  void formatter(const class formatter& formatter) { _formatter = formatter; }

  template<typename T>
  void print(T&& message) const { _print(_styler.style(std::move(message))); }

  template<typename T, typename... Args>
  void print(T&& message, Args&&... args) const { _print(_styler.style(std::move(message))); print(std::move(args)...); }


  template<typename T>
  void println(T&& message) const { _print(_styler.style(std::move(message))); _print("\n"); }

  template<typename T, typename... Args>
  void println(T&& message, Args&&... args) const { _print(_styler.style(std::move(message))); print(std::move(args)...); _print("\n"); }
}; // class printer

} // namespace output
