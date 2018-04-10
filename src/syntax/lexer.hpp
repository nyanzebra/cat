#pragma once

#include "token.hpp"

namespace syntax {

class lexer {
private:
  std::list<token> _tokens;
protected:
public:
private:
  void _lex(std::ifstream&& stream, std::string&& file) {
    if (!stream.is_open()) {
      std::cout << "Couldn't open file!";
      return;
    }
    _tokens.clear();
    std::string tok;
    bool is_string = false;
    bool is_char = false;
    size_t line = 1;
    char c;
    while (stream >> std::noskipws >> c) {
      switch (c) {
        case '/':
        {
          if (stream.peek() == '/') { // single line comments
            stream >> std::noskipws >> c;
            stream >> std::noskipws >> c; // char after '/'
            while ((c != '\n' && c != '\r')) stream >> std::noskipws >> c;
            stream >> std::noskipws >> c; // skip \n or \r
            continue;
          }
          if (stream.peek() == '*') { // multi line comments
            stream >> std::noskipws >> c;
            stream >> std::noskipws >> c; // char after '*'
            while ((c != '*' && stream.peek() != '/')) stream >> std::noskipws >> c;
            stream >> std::noskipws >> c; // skip last char of block comment
            continue;
          }
          // this should be division
          if (!tok.empty()) {
            _tokens.push_back(token(line, file, tok));
            tok = "";
          }
          _tokens.push_back(token(line, file, std::string(1, c)));
          continue;
        }
        break;
        case ' ':
        {
           if (!is_string && !is_char) {
            if (!tok.empty()) {
              _tokens.push_back(token(line, file, tok));
              tok = "";
            }
            continue;
          }
        }
        break;
        case '"':
        {
          if (is_string) { // closing "
            is_string = false;
          } else {
            is_string = true;
          }
        }
        break;
        case '\'':
        {
          if (is_char) { // closing '
            is_char = false;
          } else {
            is_char = true;
          }
        }
        break;
        case '\n':
        {
          if (!is_string && !is_char) {
            continue;
          }
        }
        break;
        case '\r':
        {
          continue; // not supported (ignored)
        }
        break;
        case '<':
        case '>':
        case ':':
        case '+':
        case '-':
        case '=':
        case '~':
        case '|':
        case '?':
        case '.':
        case '*':
        case '%':
        case '#':
        case '&':
        case '!':
        case '^':
        case ',':
        case ';':
        {
          // this should close a token
          if (!is_string && !is_char) {
            if (!tok.empty()) {
              _tokens.push_back(token(line, file, tok));
              tok = "";
            }
            _tokens.push_back(token(line, file, std::string(1, c)));
            continue;
          }
        }
        break;
        case '[':
        case '(':
        case '{':
        {
          // this should close a token
          if (!is_string && !is_char) {
            if (!tok.empty()) {
              _tokens.push_back(token(line, file, tok));
              tok = "";
            }
            _tokens.push_back(token(line, file, std::string(1, c)));
            continue;
          }
        }
        break;
        case ']':
        case ')':
        case '}':
        {
          if (!is_string && !is_char) {
            if (!tok.empty()) {
              _tokens.push_back(token(line, file, tok));
              tok = "";
            }
            _tokens.push_back(token(line, file, std::string(1, c)));
            continue;
          }
        }
        break;
        default:
        break;
      }
      tok += c;
    }

    if (!tok.empty()) {
      _tokens.push_back(token(line, file, tok));
      tok = "";
    }
  }
protected:
public:
  void lex(std::list<std::string>&& files) {
    // assert(files.size() > 0 && "Must have at least 1 file to lex for compiling...");
    for (auto file : files) {
      lex(std::forward<std::string>(file));
    }
  }

  void lex(std::string&& file) {
    // assert(file.size() > 0 && "Must lex non-empty file");
    _lex(std::ifstream(std::forward<std::string>(file)), std::forward<std::string>(file));
  }

  const std::list<token>& tokens() const {
    if (_tokens.empty()) {
      std::cout << "Couldn't read code from file" << std::endl;
    }
    return _tokens;
   }
};

} // namespace syntax
