#pragma once

#include "deps/std.hpp"

namespace output {

typedef unsigned char colour_code;

class colour {
private:
  colour_code _red;
  colour_code _green;
  colour_code _blue;
  bool _is_normalized;
protected:
public:
  // enum {
  //   kBLACK,
  //   kWHITE,
  //   kRED,
  //   kGREEN,
  //   kBLUE,
  //   kGREY,
  //   kYELLOW,
  //   kPINK,
  //   kCYAN,
  //   kPURPLE,
  //   kMAGENTA,
  //
  // }
private:
protected:
public:
  colour() : colour(0) {}
  colour(colour_code r, colour_code g, colour_code b) : _red(r), _green(g), _blue(b), _is_normalized(false) {}
  colour(unsigned int hex_code) : _red((hex_code >> 16) & 0xFF), _green((hex_code >> 8) & 0xFF), _blue(hex_code & 0xFF), _is_normalized(false) {}

  bool is_normalized() const { return _is_normalized; }
  void normalize() { _is_normalized = true; }
  void unnormalize() { _is_normalized = false; }

  friend std::ostream& operator<<(std::ostream& stream, const colour& colour) {
    stream << std::to_string(colour._red) << ";" << std::to_string(colour._green) << ";" << std::to_string(colour._blue);
    return stream;
  }
};

class styler {
private:
  std::string _ending = "\x1b[0m";
  bool _is_bold;
  bool _is_italic;
  bool _is_underlined;
  colour _foreground_colour;
  colour _background_colour;
protected:
public:
private:
protected:
public:
  styler() : _is_bold(false), _is_italic(false), _is_underlined(false) {}

  void foreground(colour colour) { _foreground_colour = colour; }
  colour& foreground() { return _foreground_colour; }
  void background(colour colour) { _background_colour = colour; }
  colour& background() { return _background_colour; }

  bool is_bold() const { return _is_bold; }
  void is_bold(bool is_bold) { _is_bold = is_bold; }

  bool is_italic() const { return _is_italic; }
  void is_italic(bool is_italic) { _is_italic = is_italic; }

  bool is_underlined() const { return _is_underlined; }
  void is_underlined(bool is_underlined) { _is_underlined = is_underlined; }

  template<typename T>
  const std::string style(T&& str) const {
    std::stringstream stream;
    if (_is_bold) {
      stream << "\033[1m";
    }
    if (_is_italic) {
      stream << "\033[3m";
    }
    if (_is_underlined) {
      stream << "\033[4m";
    }

    if (!_foreground_colour.is_normalized()) {
      stream << "\x1b[38;2;" << _foreground_colour << "m";
    }
    if (!_background_colour.is_normalized()) {
      stream << "\x1b[48;2;" << _background_colour << "m";
    }

    stream << std::move(str);

    if (!_background_colour.is_normalized()) {
      stream << _ending;
    }
    if (!_foreground_colour.is_normalized()) {
      stream << _ending;
    }

    if (_is_bold) {
      stream << "\033[21m";
    }
    if (_is_italic) {
      stream << "\033[23m";
    }
    if (_is_underlined) {
      stream << "\033[24m";
    }

    return stream.str();
  }
}; // class styler

} // namespace output
