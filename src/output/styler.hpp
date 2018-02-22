#pragma once

#include "deps/std.hpp"

namespace output {

typedef unsigned char colour_code;

class rgb {
private:
  colour_code _red;
  colour_code _green;
  colour_code _blue;
protected:
public:
private:
protected:
public:
  rgb() : rgb(0) {}
  rgb(colour_code r, colour_code g, colour_code b) : _red(r), _green(g), _blue(b) {}
  rgb(unsigned int hex_code) : _red((hex_code >> 16) & 0xFF), _green((hex_code >> 8) & 0xFF), _blue(hex_code & 0xFF) {}

  friend std::ostream& operator<<(std::ostream& stream, const rgb& colour) {
    stream << std::to_string(colour._red) << ";" << std::to_string(colour._green) << ";" << std::to_string(colour._blue);
    return stream;
  }
};

class styler {
private:
  const std::string _ending = "\x1b[0m";
  bool _is_bold;
  bool _is_italic;
  bool _is_underlined;
  rgb _foreground_colour;
  rgb _background_colour;
protected:
public:
private:
protected:
public:
  void foreground(rgb colour) { _foreground_colour = colour; }
  void background(rgb colour) { _background_colour = colour; }

  bool is_bold() const { return _is_bold; }
  void is_bold(bool is_bold) { _is_bold = is_bold; }

  bool is_italic() const { return _is_italic; }
  void is_italic(bool is_italic) { _is_italic = is_italic; }

  bool is_underlined() const { return _is_underlined; }
  void is_underlined(bool is_underlined) { _is_underlined = is_underlined; }

  template<typename T = std::string, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  const std::string style(T&& str) const {
    std::stringstream stream;
    if (_is_bold) {
      // add bold to string
    }
    if (_is_italic) {
      // add italic to string
    }
    if (_is_underlined) {
      // add underlined to string
    }

    stream << "\x1b[38;2;" << _foreground_colour << "m" << "\x1b[48;2;" << _background_colour << "m" << std::move(str) << _ending << _ending;

    if (_is_bold) {
      // remove bold from string
    }
    if (_is_italic) {
      // remove italic from string
    }
    if (_is_underlined) {
      // remove underlined from string
    }

    return stream.str();
  }
}; // class styler

} // namespace output
