#pragma once

#include "printer.hpp"

#include "deps/std.hpp"

namespace output {

// make sure T is a stream object TODO: add colours and <filename, function, line>
//template<typename T, typename = std::enable_if_t<std::is_base_of<std::ostream, T>::value>>
class logger {
private:
  printer _info_printer;
  printer _debug_printer;
  printer _warning_printer;
  printer _error_printer;
protected:
public:
private:
protected:
public:
  logger(output_type type) : _warning_printer(type), _error_printer(type), _debug_printer(type), _info_printer(type) {
    styler s;
    s.foreground().normalize();
    s.background().normalize();
    _info_printer.styler(s);

    s.foreground(colour(0, 255, 255));
    _debug_printer.styler(s);

    s.foreground(colour(255, 255, 0));
    _warning_printer.styler(s);

    s.foreground(colour(255, 0, 0));
    _error_printer.styler(s);
  }
  template<typename U, typename... Args>
  void debug(U&& msg, Args&&... args) const { _debug_printer.println("[DEBUG]: ", std::move(msg), std::move(args)...); }
  template<typename U, typename... Args>
  void info(U&& msg, Args&&... args) const { _info_printer.println("[INFO]: ", std::move(msg), std::move(args)...); }
  template<typename U, typename... Args>
  void error(U&& msg, Args&&... args) const { _error_printer.println("[ERROR]: ", std::move(msg), std::move(args)...); }
  template<typename U, typename... Args>
  void warning(U&& msg, Args&&... args) const { _warning_printer.println("[WARNING]: ", std::move(msg), std::move(args)...); }
};

} // namespace output
