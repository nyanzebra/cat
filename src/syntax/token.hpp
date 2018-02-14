#pragma once

#include "keyword.hpp"

#include <algorithm>

namespace syntax {

class token {
private:
  size_t _line;
  std::string _filename;
  std::string _value;
  token_type _type = token_type::kPOSSIBLE_ENTITY;
protected:
public:
private:
  bool is_binary() {
    if (_value.size() > 3 && _value[0] == '0' && (_value[1] == 'b' || _value[1] == 'B')) {
      for (auto i = 2u; i < _value.size(); ++i) {
        if (_value[i] < '0' || _value[i] > '1') {
          _type = token_type::kERROR;
          return false;
        }
      }
      return true;
    }
    return false;
  }

  bool is_octal() {
    if ((_value.size() > 3) && (_value[0] == '0') && (_value[1] == 'o' || _value[1] == 'O')) {
      for (auto i = 2u; i < _value.size(); ++i) {
        if (_value[i] < '0' || _value[i] > '8') {
          _type = token_type::kERROR;
          return false;
        }
      }
      return true;
    }
    return false;
  }

  bool is_hex() {
    if ((_value.size() > 3) && (_value[0] == '0') && (_value[1] == 'x' || _value[1] == 'X')) {
      for (auto i = 2u; i < _value.size(); ++i) {
        if ((_value[i] < 'a' || _value[i] > 'f') && (_value[i] < 'A' || _value[i] > 'F') && (_value[i] < '0' || _value[i] > '9')) {
          _type = token_type::kERROR;
          return false;
        }
      }
      return true;
    }
    return false;
  }

  bool is_number() {
    size_t dot_count = 0;
    for (auto i = (long long)(_value.size() - 1); i >= 0; --i) {
      if (_value[i] == 'u' && i == _value.size() - 1) {
        // if 'u' is present it best be an unsigned :)
        _type = token_type::kUNSIGNED_INTEGER_LITERAL;
        continue;
      }
      if (_value[i] < '0' || _value[i] > '9') {
        if (_value[i] == '.') {
          if (_type == token_type::kUNSIGNED_INTEGER_LITERAL) {
            _type = token_type::kERROR;
            return false;
          }
          // if '.' it best be a float :)
          _type = token_type::kFLOAT_LITERAL;
          dot_count++;
          if (dot_count > 1) {
            _type = token_type::kERROR;
            return false;
          }
        } else if (_value[i] == ',') {
          if ((i - 1) % 3 != 0) {
            _type = token_type::kERROR;
            return false;
          }
          if (i == 0) {
            _type = token_type::kERROR;
            return false;
          }
        } else {
          _type = token_type::kERROR;
          return false;
        }
      }
    }
    return true;
  }

  bool is_keyword() const { return (gKEYWORDS.find(_value) != gKEYWORDS.end()); }

  bool is_char() {
    if ((*_value.begin() != '\'' && *(_value.end() - 1) == '\'')) {
      _type = token_type::kERROR;
      return false;
    } else if ((*_value.begin() == '\'' && *(_value.end() - 1) != '\'')) {
      _type = token_type::kERROR;
      return false;
    } else if ((*_value.begin() == '\'' && *(_value.end() - 1) == '\'')) {
      return true;
    }
    return false;
  }

  bool is_string() {
    if ((*_value.begin() != '"' && *(_value.end() - 1) == '"')) {
      _type = token_type::kERROR;
      return false;
    } else if ((*_value.begin() == '"' && *(_value.end() - 1) != '"')) {
      _type = token_type::kERROR;
      return false;
    } else if ((*_value.begin() == '"' && *(_value.end() - 1) == '"')) {
      return true;
    }
    return false;
  }

  bool is_opening_delimiter() const { return (_value == "(" || _value == "[" || _value == "{"); }

  bool is_closing_delimiter() const { return (_value == ")" || _value == "]" || _value == "}"); }

  bool is_semi_colon() const { return _value == ";"; }

  bool is_comma() const { return _value == ","; }

  bool is_entity() {
    if (!is_string() && !is_char()) {
      if ((*_value.begin() != '"' && *(_value.end() - 1) == '"')) {
        _type = token_type::kERROR;
        return false;
      }
      if ((*_value.begin() == '"' && *(_value.end() - 1) != '"')) {
        _type = token_type::kERROR;
        return false;
      }
      if ((*_value.begin() != '\'' && *(_value.end() - 1) == '\'')) {
        _type = token_type::kERROR;
        return false;
      }
      if ((*_value.begin() == '\'' && *(_value.end() - 1) != '\'')) {
        _type = token_type::kERROR;
        return false;
      }
      if (_value[0] >= '0' && _value[0] <= '9') {
        return false;
      }
      for (auto i = 1u; i < _value.size(); ++i) {
        if (!((_value[i] >= '0' && _value[i] <= '9') || (_value[i] >= 'a' && _value[i] <= 'z') || (_value[i] >= 'A' && _value[i] <= 'Z') || (_value[i] == '_'))) {
          return false;
        }
      }
      return true;
    }
    return false;
  }

  bool is_operator(char c) const {
    switch(c) {
      case '~':
      case '!':
      case '%':
      case '^':
      case '*':
      case '-':
      case '+':
      case '=':
      case '<':
      case '>':
      case '?':
      case '/':
      case ':':
      case ',':
      case '.':
      case '|':
        return true;
      default:
        return false;
    }
  }

  bool is_operator() const { return is_operator(_value[0]) && _value.size() > 1; }
protected:
public:
  template<typename T, typename U, typename = std::enable_if_t<std::is_constructible<std::string, T>::value && std::is_constructible<std::string, U>::value>>
  token(const size_t line, T&& filename, U&& value) : _line(line), _filename(std::forward<T>(filename)), _value(std::move(value)) {
    if (is_number() || is_hex() || is_octal() || is_binary()) {
      if (_type != token_type::kUNSIGNED_INTEGER_LITERAL && _type != token_type::kFLOAT_LITERAL) _type = token_type::kINTEGER_LITERAL;
      auto it = std::remove_if(_value.begin(),_value.end(), [&](char c) { return c == ',' || c == 'u'; });
      _value.erase(it, _value.end());
    } else if (is_char()) {
      _type = token_type::kCHAR_LITERAL;
    } else if (is_string()) {
      _type = token_type::kSTRING_LITERAL;
    } else if (is_opening_delimiter()) {
      _type = token_type::kOPENING_DELIMITER;
    } else if(is_closing_delimiter()) {
      _type = token_type::kCLOSING_DELIMITER;
    } else if(is_semi_colon()) {
      _type = token_type::kTERMINATOR;
    } else if (is_comma()) {
      _type = token_type::kSEPARATOR;
    } else if (is_keyword()) {
      _type = gKEYWORDS.at(_value);
    } else if (is_operator() && _value.size() == 1) {
      _type = token_type::kOPERATOR;
    } else if (is_entity()) {
      _type = token_type::kPOSSIBLE_ENTITY;
      if (is_operator(_value[0])) {
        _type = token_type::kERROR;
      }
    } else {
      _type = token_type::kERROR;
    }
  }
  template<typename T, typename U, typename = std::enable_if_t<std::is_constructible<std::string, T>::value && std::is_constructible<std::string, U>::value>>
  token(const size_t line, T&& filename, U&& value, const token_type type) : _line(line), _filename(std::move(filename)), _value(std::move(value)), _type(type) {
    if (type == token_type::kFLOAT_LITERAL || type == token_type::kINTEGER_LITERAL ||type == token_type::kUNSIGNED_INTEGER_LITERAL) {
      auto it = std::remove_if(_value.begin(),_value.end(), [&](char c) { return c == ',' || c == 'u'; });
      _value.erase(it, _value.end());
    }
  }

  friend bool operator==(const token& tok, const token_type type) { return tok.type() == type; }
  friend std::ostream& operator<<(std::ostream& o, const token& tok) {
    o << "{";
    o << "\n\tline: " << tok.line() << ",";
    o << "\n\tfile: \"" << tok.filename() << "\",";
    o << "\n\tvalue: \"" << tok.value() << "\",";
    o << "\n\ttype: " << gTOKEN_NAMES.at(tok.type());
    o << "\n}";
    return o;
  }

  const size_t& line() const { return _line; }
  const std::string& filename() const { return _filename; }
  const std::string& value() const { return _value; }
  const token_type& type() const { return _type; }
};

} // namespace syntax
