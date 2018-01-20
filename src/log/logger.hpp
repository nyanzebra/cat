#pragma once

#include <iostream>
#include <type_traits>

namespace logger {

// make sure T is a stream object TODO: add colours and <filename, function, line>
template<typename T, typename = std::enable_if_t<std::is_base_of<std::ostream, T>::value>>
class base_logger : T {
public:
  template<typename U, typename = std::enable_if_t<std::is_convertible<std::string, U>::value>>
  void info(U&& msg) const { /*(*(this)) << "[INFO]: " << msg << std::endl; */}
  template<typename U, typename = std::enable_if_t<std::is_convertible<std::string, U>::value>>
  void error(U&& msg) const { /*(*(this)) << "[ERROR]: " << msg << std::endl; */}
  template<typename U, typename = std::enable_if_t<std::is_convertible<std::string, U>::value>>
  void warning(U&& msg) const { /*(*(this)) << "[WARNING]: " << msg << std::endl; */}
};

template<typename T, typename = std::enable_if_t<std::is_base_of<std::ofstream, T>::value>>
using file_logger = base_logger<T>;

template<typename T, typename = std::enable_if_t<std::is_base_of<std::ostringstream, T>::value>>
using string_logger = base_logger<T>;

template<typename T = std::ostream>
using logger = base_logger<T>;

}
