#pragma once

#include <iostream>
#include <type_traits>

namespace log {

// make sure T is a stream object TODO: add colours and <filename, function, line>
template<typename T, typename = std::enable_if_t<std::is_base_of_v<std::ostream, T>>>
class base_logger : T {
public:
  template<typename U, typename = std::enable_if_t<std::is_convertible_v<std::string, U>>>
  void info(U&& msg) const { /*(*(this)) << "[INFO]: " << msg << std::endl; */}
  template<typename U, typename = std::enable_if_t<std::is_convertible_v<std::string, U>>>
  void error(U&& msg) const { /*(*(this)) << "[ERROR]: " << msg << std::endl; */}
  template<typename U, typename = std::enable_if_t<std::is_convertible_v<std::string, U>>>
  void warning(U&& msg) const { /*(*(this)) << "[WARNING]: " << msg << std::endl; */}
};

template<typename T, typename = std::enable_if_t<std::is_base_of_v<std::ofstream, T>>>
using file_logger = base_logger<T>;

template<typename T, typename = std::enable_if_t<std::is_base_of_v<std::ostringstream, T>>>
using string_logger = base_logger<T>;

template<typename T = std::ostream>
using logger = base_logger<T>;

}
