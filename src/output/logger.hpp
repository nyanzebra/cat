#pragma once

#include "printer.hpp"

#include "deps/std.hpp"

namespace output {

// make sure T is a stream object TODO: add colours and <filename, function, line>
//template<typename T, typename = std::enable_if_t<std::is_base_of<std::ostream, T>::value>>
class logger {
private:
  printer _printer;
protected:
public:
private:
protected:
public:
#ifdef DEBUG
  logger() : _printer(output_type::kSTANDARD_OUTPUT) {}
#else
  logger() : _printer(output_type::kNULL) {}
#endif
  logger(output_type type) : _printer(type) {}
  template<typename U, typename... Args>
  void debug(U&& msg, Args&&... args) const { _printer.print("[DEBUG]: ", std::move(msg), std::move(args)...); }
  template<typename U, typename... Args>
  void info(U&& msg, Args&&... args) const { _printer.print("[INFO]: ", std::move(msg), std::move(args)...); }
  template<typename U, typename... Args>
  void error(U&& msg, Args&&... args) const { _printer.print("[ERROR]: ", std::move(msg), std::move(args)...); }
  template<typename U, typename... Args>
  void warning(U&& msg, Args&&... args) const { _printer.print("[WARNING]: ", std::move(msg), std::move(args)...); }
};

// template<typename T, typename = std::enable_if_t<std::is_base_of<std::ofstream, T>::value>>
// using file_logger = base_logger<T>;
//
// template<typename T, typename = std::enable_if_t<std::is_base_of<std::ostringstream, T>::value>>
// using string_logger = base_logger<T>;
//
// template<typename T = std::ostream>
// using logger = base_logger<T>;

} // namespace output
