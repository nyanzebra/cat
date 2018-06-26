#pragma once

#include "ast.hpp"
#include "token.hpp"
#include "scope.hpp"

#include "deps/std.hpp"
#include "output/logger.hpp"

namespace syntax {

class parser {
private:
  typedef std::list<token> token_list;
  typedef token_list::const_iterator token_list_iterator;

  output::logger _log;
protected:
public:
private:
protected:
  bool is_valid_type(const token_list_iterator it, const token_type type) const {
    if (it->type() == type) {
      return true;
    }
    return false;
  }
  bool is_valid_value(const token_list_iterator it, std::string value) const {
    if (it->value() == value) {
      return true;
    }
    return false;
  }
  template<typename T, typename = std::enable_if_t<std::is_constructible<std::string, T>::value>>
  bool is_valid_token(const token_list_iterator it, const token_type type, T&& value) const { return is_valid_type(it, type) && is_valid_value(it, std::forward<T>(value)); }

  std::unique_ptr<ast_bool> parse_bool(token_list_iterator& begin, const token_list_iterator& end) const {
    if (std::distance(begin, end) <= 0) return nullptr;
    if (is_valid_type(begin, token_type::kBOOL_LITERAL)) {
      if (is_valid_value(begin, "false")) {
        ++begin; // eat false
        return std::make_unique<ast_bool>(false);
      }
      if (is_valid_value(begin, "true")) {
        ++begin; // eat true
        return std::make_unique<ast_bool>(true);
      }
      _log.error("Invalid token, somehow a bool literal not of value true or false");
    }
    return nullptr;
  }

  std::unique_ptr<ast_char> parse_char(token_list_iterator& begin, const token_list_iterator& end) const {
    if (std::distance(begin, end) <= 0) return nullptr;
    if (is_valid_type(begin, token_type::kCHAR_LITERAL)) {
      auto res = std::make_unique<ast_char>(begin->value()[1]); // '\'','a', '\''
      ++begin; // eat
      return res;
    }
    return nullptr;
  }

  std::unique_ptr<ast_int64> parse_integer(token_list_iterator& begin, const token_list_iterator& end) const {
    if (std::distance(begin, end) <= 0) return nullptr;
    if (is_valid_type(begin, token_type::kINTEGER_LITERAL)) {
      std::stringstream stream(begin->value());
      long long literal;
      stream >> literal;
      ++begin; // eat
      return std::make_unique<ast_int64>(literal);
    }
    return nullptr;
  }

  std::unique_ptr<ast_int64> parse_unsigned_integer(token_list_iterator& begin, const token_list_iterator& end) const {
    if (std::distance(begin, end) <= 0) return nullptr;
    if (is_valid_type(begin, token_type::kUNSIGNED_INTEGER_LITERAL)) {
      std::stringstream stream(begin->value());
      unsigned long long literal;
      stream >> literal;
      ++begin; // eat
      return std::make_unique<ast_int64>(literal);
    }
    return nullptr;
  }

  std::unique_ptr<ast_flt64> parse_float(token_list_iterator& begin, const token_list_iterator& end) const {
    if (std::distance(begin, end) <= 0) return nullptr;
    if (is_valid_type(begin, token_type::kFLOAT_LITERAL)) {
      std::stringstream stream(begin->value());
      double literal;
      stream >> literal;
      ++begin; // eat
      return std::make_unique<ast_flt64>(literal);
    }
    return nullptr;
  }

  std::unique_ptr<ast_string> parse_string(token_list_iterator& begin, const token_list_iterator& end) const {
    if (std::distance(begin, end) <= 0) return nullptr;
    if (is_valid_type(begin, token_type::kSTRING_LITERAL)) {
      auto res = std::make_unique<ast_string>(begin->value());
      ++begin; // eat
      return res;
    }
    return nullptr;
  }

  std::unique_ptr<ast_type> parse_type(token_list_iterator& begin, const token_list_iterator& end) const {
    if (std::distance(begin, end) <= 0) return nullptr;
    auto mods = try_read_modifiers(begin, end);
    if (begin->type() == token_type::kTYPE || begin->type() == token_type::kPOSSIBLE_ENTITY) {
      auto value = begin->value();
      ++begin;
      auto res = std::make_unique<ast_type>(value, mods);
      mods = try_read_modifiers(begin, end);
      if (mods != modifiers::kNONE) {
        _log.error("Type modifiers must come before type");
      }
      return res;
    }
    return nullptr;
  }

  // TODO: create a parse conditional function
  // it should check to see if only one expression is present and that it evaluates a boolean
  // if more than one exists, make sure assignment is first, then condition, then whatever else
  std::unique_ptr<ast_expression> parse_parentheses(token_list_iterator& begin, const token_list_iterator& end) const {
    if (std::distance(begin, end) <= 0) return nullptr;
    if (!is_valid_token(begin, token_type::kOPENING_DELIMITER, "(")) return nullptr;
    ++begin; // eat '('
    auto value = parse_expression(begin, end);
    if (!is_valid_token(begin, token_type::kCLOSING_DELIMITER, ")")) return nullptr;
    ++begin; // eat ')'
    return value;
  }

  modifiers try_read_modifiers(token_list_iterator& begin, const token_list_iterator& end) const {
    modifiers mods = modifiers::kNONE;
    if (std::distance(begin, end) <= 0) return mods;
    while (is_valid_type(begin, token_type::kTYPE_MODIFIER)) {
      if (is_valid_value(begin, "volatile")) {
        if (mods & modifiers::kVOLATILE) {
          _log.warning("Modifier volatile found twice");
        }
        mods |= modifiers::kVOLATILE;
        ++begin;
        continue;
      }
      if (is_valid_value(begin, "extern")) {
        if (mods & modifiers::kEXTERN) {
          _log.warning("Modifier extern found twice");
        }
        mods |= modifiers::kEXTERN;
        ++begin;
        continue;
      }
      if (is_valid_value(begin, "static")) {
        if (mods & modifiers::kSTATIC) {
          _log.warning("Modifier static found twice");
        }
        mods |= modifiers::kSTATIC;
        ++begin;
        continue;
      }
      if (is_valid_value(begin, "mutable")) {
        if (mods & modifiers::kMUTABLE) {
          _log.warning("Modifier mutable found twice");
        }
        mods |= modifiers::kMUTABLE;
        ++begin;
        continue;
      }
    }
    return mods;
  }

  std::unique_ptr<ast_function_call> parse_function_call(token_list_iterator& begin, const token_list_iterator& end) const {
    return nullptr;
  }

  std::unique_ptr<ast_function_prototype> parse_function_prototype(token_list_iterator& begin, const token_list_iterator& end, const std::string& name, std::unique_ptr<ast_type> ret) const {
    if (std::distance(begin, end) <= 0) {
      _log.error("Trying to parse a function prototype without remaining tokens");
      return nullptr;
    }
    if (is_valid_token(begin, token_type::kOPENING_DELIMITER, "(")) { // we have a function!
      ++begin; // eat "("
      auto it_begin = begin;
      auto it_end = it_begin;
      std::list<std::unique_ptr<ast_type>> args;

      while (!is_valid_token(it_end, token_type::kCLOSING_DELIMITER, ")")) {
        ++it_end;
        if (is_valid_token(it_end, token_type::kSEPARATOR, ",")) {
          args.push_back(std::move(parse_type(it_begin, it_end)));
          it_begin = it_end;
        }
      }

      if (is_valid_token(it_end, token_type::kCLOSING_DELIMITER, ")") && it_begin != it_end) {
        args.push_back(parse_type(it_begin, it_end));
        it_begin = it_end;
      }

      if (is_valid_token(it_end, token_type::kCLOSING_DELIMITER, ")")) ++begin;

      return std::make_unique<ast_function_prototype>(name, std::move(ret), std::move(args));
    } else { // it must be a variable, we return null here because variable will be made elsewhere
      return nullptr;
    }
  }

  std::unique_ptr<ast_function> parse_function(token_list_iterator& begin, const token_list_iterator& end) const {
    // TODO
    if (std::distance(begin, end) <= 0) {
      _log.error("Trying to parse a function without remaining tokens");
      return nullptr;
    }
    auto it = begin;
    auto type = parse_type(begin, end);
    if (!type) return nullptr;
    if (begin->type() != token_type::kPOSSIBLE_ENTITY) return nullptr;
    _log.debug("type: ", type->name());
    auto name_token = *begin;
    auto name = name_token.value();
    // TODO: name check here
    ++begin; // eat name?
    _log.debug("name: ", name);
    if (auto prototype = parse_function_prototype(begin, end, name, std::move(type))) {
      // try and parse a body
      _log.debug("value is ", begin->value(), "of type ", gTOKEN_NAMES.at(begin->type()));
      if (auto body = parse_block(begin, end)) {
        return std::make_unique<ast_function>(std::move(prototype), std::move(body));
      }
      _log.error("Function must have a body");
      return nullptr;
    }
    _log.debug("No prototype for function");
    return nullptr;
  }

  std::unique_ptr<ast_variable> parse_variable(token_list_iterator& begin, const token_list_iterator& end) const {
    if (std::distance(begin, end) <= 0) {
      _log.error("Trying to parse a variable/function without remaining tokens");
      return nullptr;
    }
    auto it = begin;
    auto type = parse_type(begin, end);
    if (!type) {
      _log.debug("Could not get type for variable");
      return nullptr;
    }
    if (begin->type() != token_type::kPOSSIBLE_ENTITY) {
      std::cout << "2. type: " << *begin << std::endl;
      _log.debug("Name is not a possible entity found : ", gTOKEN_NAMES.at(begin->type()), " for ", begin->value());
      return nullptr;
    }
    auto name_token = *begin;
    auto name = name_token.value();
    // TODO: name check here
    ++begin; // eat name?
    // if there is no ( then it must be a variable
    if (is_valid_token(begin, token_type::kTERMINATOR, ";")) {
      ++begin; // eat ';'
      _log.debug("begin: ", begin->value());
      return std::make_unique<ast_variable>(name, std::move(type));
    }
    if (is_valid_value(begin, "=")) {
      ++begin; // eat '='
      auto val = parse_primary(begin, end); // ; take care of by parse_expression
      if (!is_valid_token(begin, token_type::kTERMINATOR, ";")) {
        _log.error("Assignment statement must end with ';'");
        return nullptr;
      }
      ++begin; // eat ;
      return std::make_unique<ast_variable>(name, std::move(type), std::move(val));
      // we need to assign value to a variable
    }
    if (is_valid_token(begin, token_type::kOPENING_DELIMITER, "(")) {
      auto it = begin;
      while (!is_valid_token(it, token_type::kCLOSING_DELIMITER, ")")) ++it;
      if (is_valid_token(it, token_type::kOPENING_DELIMITER, "{")) {
        // must be a function
        return nullptr;
      }
      if (is_valid_token(begin, token_type::kTERMINATOR, ";")) {
        // constructor stuff
      }
    }
    return nullptr;
  }

  // TODO: this function must have its' results checked later that the symbol definition exists, otherwise error
  std::unique_ptr<ast_expression> parse_identifier(token_list_iterator& begin, const token_list_iterator& end) const {
    if (std::distance(begin, end) <= 0) return nullptr;
    auto tok = *begin++;
    if (!is_valid_token(begin, token_type::kOPENING_DELIMITER, "(")) return nullptr;//return std::make_unique<ast_variable>(tok.value()); // TODO: change this to correct type
    if (is_valid_token(begin, token_type::kOPENING_DELIMITER, "(")) {
      std::list<std::unique_ptr<ast_expression>> args;
      while (!is_valid_token(begin, token_type::kCLOSING_DELIMITER, ")")) {
        if (auto arg = parse_expression(begin, end)) {
          args.push_back(std::move(arg));
        }
        if (is_valid_token(begin, token_type::kCLOSING_DELIMITER, ")")) break;
        if (!is_valid_type(begin, token_type::kSEPARATOR)) {
          // log error
          return nullptr;
        }
        ++begin;
      }

      if (is_valid_token(begin, token_type::kCLOSING_DELIMITER, ")")) ++begin;
      return nullptr;//std::make_unique<ast_function_call>(new ast_function_call(tok.value(), std::move(args)));
    }

    return nullptr;
  }

  // need to see if lhs is null then see if unary operator if not see if binary
  std::unique_ptr<ast_expression> parse_binary_operation_expression(token_list_iterator& begin, const token_list_iterator& end, std::unique_ptr<ast_expression> lhs) const {
    if (std::distance(begin, end) <= 0) return lhs;
    if (!lhs) return nullptr;
    return lhs;
  }

  std::unique_ptr<ast_for> parse_for(token_list_iterator& begin, const token_list_iterator& end) const {
    if (std::distance(begin, end) <= 0) return nullptr;
    return nullptr;
    // if (!is_valid_token(begin, token_type::kFOR, "for")) return nullptr;
    // ++begin; // eat 'for'
    // ++begin; // eat '('
    // auto start = parse_variable(begin, end);
    // if (!start) {
    //   // log error
    //   return nullptr;
    // }
    // auto condition = parse_binary_operation_expression(begin, end, nullptr);
    // if (!condition) {
    //   // log error
    //   return nullptr;
    // }
    // auto term = parse_binary_operation_expression(begin, end, nullptr);
    // if (!term) {
    //   // log error
    //   return nullptr;
    // }
    // auto body = parse_block(begin, end);
    // return std::make_unique<ast_for>(start, condition, term, body);
  }

  std::unique_ptr<ast_while> parse_while(token_list_iterator& begin, const token_list_iterator& end) const { return nullptr; }

  std::unique_ptr<ast_try> parse_try(token_list_iterator& begin, const token_list_iterator& end) const { return nullptr; }

  std::unique_ptr<ast_arm> parse_arm(token_list_iterator& begin, const token_list_iterator& end) const { return nullptr; }

  std::unique_ptr<ast_match> parse_match(token_list_iterator& begin, const token_list_iterator& end) const { return nullptr; }

  std::unique_ptr<ast_if> parse_if(token_list_iterator& begin, const token_list_iterator& end) const {
    if (std::distance(begin, end) <= 0) {
      _log.error("Trying to parse an if without remaining tokens");
      return nullptr;
    }
    if (!is_valid_token(begin, token_type::kIF, "if")) {
      _log.error("if statement must start with 'if'");
      return nullptr;
    }

    ++begin; // eat 'if'
    auto condition = parse_parentheses(begin, end); // should capture condition

    if (!condition) {
      _log.error("Cannot have an empty condition in if");
      return nullptr;
    }
    auto then = parse_expression(begin, end);
    if (is_valid_token(begin, token_type::kELSE, "else")) {
      ++begin; // eat else
      auto other = parse_expression(begin, end);
      return std::make_unique<ast_if>(std::move(condition), std::move(then), std::move(other));
    }

    return std::make_unique<ast_if>(std::move(condition), std::move(then), nullptr);
  }

  std::unique_ptr<ast_return> parse_return(token_list_iterator& begin, const token_list_iterator& end) const {
    if (std::distance(begin, end) <= 0) return nullptr;
    ++begin; //eat return
    auto res = std::make_unique<ast_return>(parse_expression(begin, end));

    if (!res) return nullptr; // should have an error
    return res;
  }

  std::unique_ptr<ast_expression> parse_primary(token_list_iterator& begin, const token_list_iterator& end) const {
    if (std::distance(begin, end) <= 0) return nullptr;
    auto tok = *begin;
    auto it = begin;
    auto var = std::move(parse_variable(it, end));
    if (var) {
      begin = it;
      return var;
    }
    it = begin;
    auto fn = std::move(parse_function(it, end));
    if (fn) {
      begin = it;
      return fn;
    }
    switch (tok.type()) {
      case token_type::kRETURN:
        return parse_return(begin, end);
      case token_type::kSTRING_LITERAL:
        return parse_string(begin, end);
      case token_type::kCHAR_LITERAL:
        return parse_char(begin, end);
      case token_type::kFLOAT_LITERAL:
        return parse_float(begin, end);
      case token_type::kINTEGER_LITERAL:
        return parse_integer(begin, end);
      case token_type::kUNSIGNED_INTEGER_LITERAL:
        return parse_unsigned_integer(begin, end);
      case token_type::kBOOL_LITERAL:
        return parse_bool(begin, end);
      case token_type::kPOSSIBLE_ENTITY:
        return parse_identifier(begin, end);
      case token_type::kIF:
        return parse_if(begin, end);
      case token_type::kMATCH:
        return parse_match(begin, end);
      case token_type::kARM:
        return parse_arm(begin, end);
      case token_type::kFOR:
        return parse_for(begin, end);
      case token_type::kDO:
      case token_type::kWHILE:
        return parse_while(begin, end);
      case token_type::kTRY:
      case token_type::kCATCH:
        return parse_try(begin, end);
      default:
        break;
    }
    if (is_valid_token(begin, token_type::kOPENING_DELIMITER, "{")) return parse_block(begin, end);
    return nullptr;
  }

  std::unique_ptr<ast_expression> parse_expression(token_list_iterator& begin, const token_list_iterator& end) const {
    if (std::distance(begin, end) <= 0) return nullptr;
    auto lhs = parse_primary(begin, end);
    if (lhs) return parse_binary_operation_expression(begin, end, std::move(lhs));
    return nullptr;
  }

  std::unique_ptr<ast_program> parse_program(token_list_iterator& begin, const token_list_iterator& end) const {
    if (std::distance(begin, end) <= 0) return nullptr;
    auto program = std::unique_ptr<ast_program>(new ast_program());
    auto max_fails = 3u;
    auto fails = 0u;
    while (begin != end) {
      auto it = begin;
      _log.debug("adding expression to program (b != e) is ", (begin != end), " and value is ", begin->value());
      program->add_expression(std::move(parse_expression(begin, end)));
      if (it == begin) {
        _log.debug("Failure");
        ++fails;
      }
      if (fails == max_fails) {
        _log.error("Max failures during compilation, cannot continue");
        return nullptr;
      }
    }
    _log.debug("Created program");
    return program;
  }

  std::unique_ptr<ast_block> parse_block(token_list_iterator& begin, const token_list_iterator& end) const {
    if (std::distance(begin, end) <= 0) {
      _log.error("Trying to parse a block without remaining tokens");
      return nullptr;
    }
    if (is_valid_token(begin, token_type::kTERMINATOR, ";")) {
      _log.error("Found terminating token, therefore cannot parse block");
      return nullptr;
    }
    if (!is_valid_token(begin, token_type::kOPENING_DELIMITER, "{")) {
      _log.error("Cannot parse block without '{'");
      return nullptr;
    }
    ++begin; // eat '{'
    std::unique_ptr<ast_block> block(new ast_block());
    while (begin != end) { // block must look like { code }
    _log.debug("adding expression to program (b != e) is ", (begin != end), " and value is ", begin->value());
      if (is_valid_token(begin, token_type::kCLOSING_DELIMITER, "}")) {
        ++begin; // eat '}'
        return block;
      }
      auto expr = parse_expression(begin, end);
      _log.debug("adding expression to program (b != e) is ", (begin != end), " and value is ", begin->value());
      if (expr) {
        expr->print(std::cout);
        std::cout << "1. type: " << static_cast<size_t>(begin->type()) << std::endl;
        _log.debug("begin: ", begin->value(), " | ", gTOKEN_NAMES.at(begin->type()));
        block->add_expression(std::move(expr));
      } else {
        ++begin;
        // log warning?
      }
    }
    _log.debug("bad block");
    return nullptr;
  }
public:
  parser() : _log(output::logger(output::output_type::kSTANDARD_OUTPUT)) {
  }

  std::unique_ptr<ast_program> parse(const std::list<token>& tokens) const {
    // find a non-kPOSSIBLE_ENTITY token and then read until reach a kPOSSIBLE_ENTITY
    // the set of tokens should make up an expression...
    //auto begin = tokens.begin();
    //auto end = tokens.end();
    // make expression
    auto begin = tokens.cbegin();
    auto end = tokens.cend();
    return parse_program(begin, end);
    // need to keep track of imports manually...
    // so need to use the scope objects to hold objects/functions
    // then need to see if have to build imported file
    // NOTE: should not have any issues with naming conflicts across files since using import as or using namespace is not allowed
  }
}; // class parser

} // namespace syntax
