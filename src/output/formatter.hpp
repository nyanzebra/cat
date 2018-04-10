#pragma once

#include "deps/std.hpp"

namespace output {

class formatter {
private:
  size_t _tabs;
  std::string _header;
  std::string _footer;
protected:
public:
private:
protected:
public:
  formatter() : formatter("", "", 0) {}
  template<typename T = std::string, typename U = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value && std::is_constructible<std::string, U>::value>>
  formatter(T&& header, U&& footer, size_t tabs) : _header(std::move(header)), _footer(std::move(footer)), _tabs(tabs) {}

  template<typename T = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  const std::string format(T&& str) const {
    std::stringstream stream;

    stream << _header;

    stream << str;

    stream << _footer;

    return stream.str();
  }

  const std::string& header() const { return _header; }
  template<typename T = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  void header(const T& header) { _header = header; }
  template<typename T = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  void header(T&& header) { _header = std::move(header); }

  const std::string& footer() const { return _footer; }
  template<typename T = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  void footer(const T& footer) { _footer = footer; }
  template<typename T = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  void footer(T&& footer) { _footer = std::move(footer); }

  const size_t& tabs() const { return _tabs; }
  void tabs(size_t tabs) { _tabs = tabs; }
}; // class formatter

} // namespace output
