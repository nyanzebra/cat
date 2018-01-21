#pragma once

#include "ast.hpp"
#include "token.hpp"

#include "log/logger.hpp"

#include "deps/std.hpp"

namespace syntax {

class parser {
private:
  typedef std::list<token> token_list;
  typedef token_list::const_iterator token_list_iterator;
  logger::logger<std::ostream> _log;
protected:
public:
private:
protected:
  bool is_valid_type(const token_list_iterator it, const token_type type) const {
    if (it->type() == type) {
      return true;
    }
    _log.error("Type " + gTOKEN_NAMES.at(it->type()) + " is not equal to " + gTOKEN_NAMES.at(type));
    return false;
  }
  bool is_valid_value(const token_list_iterator it, const std::string& value) const {
    if (it->value() == value) {
      return true;
    }
    _log.error("Value " + it->value() + " is not equal to " + value);
    return false;
  }
  bool is_valid_token(const token_list_iterator it, const token_type type, const std::string& value) const { return is_valid_type(it, type) && is_valid_value(it, value); }

  std::unique_ptr<ast_type> parse_type(token_list_iterator begin, const token_list_iterator end) const {
    if (std::distance(begin, end) <= 0) return nullptr;
    modifiers mods;

    while (begin->type() == token_type::kTYPE) {
      if (begin->value() == "extern") {
        mods |= modifiers::kEXTERN;
      }
      if (begin->value() == "static") {
        mods |= modifiers::kSTATIC;
      }
      if (begin->value() == "mutable") {
        mods |= modifiers::kMUTABLE;
      }
      if (begin->value() == "volatile") {
        mods |= modifiers::kVOLATILE;
      }
      ++begin;
    }

    return std::make_unique<ast_type>(begin->value(), mods);
  }

  std::unique_ptr<ast_expression> parse_parentheses(token_list_iterator begin, const token_list_iterator end) const {
    if (std::distance(begin, end) <= 0) return nullptr;
    if (!is_valid_token(begin, token_type::kOPENING_DELIMITER, "(")) return nullptr;
    ++begin; // eat '('
    auto value = parse_expression(begin, end);
    if (!is_valid_token(begin, token_type::kCLOSING_DELIMITER, ")")) return nullptr;
    return value;
  }

  std::pair<modifiers, token_list_iterator> try_read_modifiers(token_list_iterator begin, const token_list_iterator end) const {
    modifiers mods = modifiers::kNONE;
    if (std::distance(begin, end) <= 0) return std::make_pair(mods, begin);
    auto it = begin;
    while (is_valid_type(it, token_type::kTYPE_MODIFIER)) {
      if (is_valid_value(it, "volatile")) {
        if (mods & modifiers::kVOLATILE) {
          // log warning
        }
        mods &= modifiers::kVOLATILE;
      }
      if (is_valid_value(it, "extern")) {
        if (mods & modifiers::kEXTERN) {
          // log warning
        }
        mods &= modifiers::kEXTERN;
      }
      if (is_valid_value(it, "static")) {
        if (mods & modifiers::kSTATIC) {
          // log warning
        }
        mods &= modifiers::kSTATIC;
      }
      if (is_valid_value(it, "mutable")) {
        if (mods & modifiers::kMUTABLE) {
          // log warning
        }
        mods &= modifiers::kMUTABLE;
      }
      ++it;
    }
    return std::make_pair(mods, it);
  }

  std::unique_ptr<ast_function> parse_function(token_list_iterator begin, const token_list_iterator end, const token& name, const token& type, const modifiers mods) const {
    // TODO
    return nullptr;
  }

  std::unique_ptr<ast_variable> parse_variable(token_list_iterator begin, const token_list_iterator end) const {
    if (std::distance(begin, end) <= 0) return nullptr;
    auto it = begin;

    auto result = try_read_modifiers(begin, end);
    modifiers mods;
    if (std::distance(result.second, begin) < 0) { // if we found any modifiers this will be true
      mods = result.first;
      begin = result.second;
    }

    auto type_token = *begin++; // next has to be a type

    result = try_read_modifiers(begin, end);
    if (std::distance(result.second, begin) < 0) {
      //log error, this means we have type modifiers after the type
      return nullptr;
    }

    auto name_token = *begin++;

    // if there is no ( then it must be a variable
    if (!is_valid_token(begin, token_type::kOPENING_DELIMITER, "(")) return nullptr;//return std::make_unique<ast_variable>(name_token.value(), type_token.value(), mods);
    // else this is a function
    //if (is_valid_token(begin, token_type::kOPENING_DELIMITER, "(")) return parse_function(begin, end, name_token, type_token, mods);
    // log error? warning?
    return nullptr;
  }

  // TODO: this function must have its' results checked later that the symbol definition exists, otherwise error
  std::unique_ptr<ast_expression> parse_identifier(token_list_iterator begin, const token_list_iterator end) const {
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

  std::unique_ptr<ast_expression> parse_binary_operation_expression(token_list_iterator begin, const token_list_iterator end, std::unique_ptr<ast_expression> lhs) const {
    if (std::distance(begin, end) <= 0) return nullptr;
    if (!lhs) return nullptr;
    return nullptr;
  }

  std::unique_ptr<ast_expression> parse_primary(token_list_iterator begin, const token_list_iterator end) const {
    if (std::distance(begin, end) <= 0) return nullptr;
    auto tok = *begin;
    switch (tok.type()) {
      case token_type::kNUMBER:
        return parse_type(begin, end);
      case token_type::kPOSSIBLE_ENTITY:
        return parse_identifier(begin, end);
      default:
        return nullptr;
    }
  }

  std::unique_ptr<ast_expression> parse_expression(token_list_iterator begin, const token_list_iterator end) const {
    auto lhs = parse_primary(begin, end);
    if (lhs) return parse_binary_operation_expression(begin, end, std::move(lhs));
    return nullptr;
  }

  std::unique_ptr<ast_program> parse_program(token_list_iterator begin, const token_list_iterator end) const {
    if (std::distance(begin, end) <= 0) return nullptr;
    //auto program = std::make_unique<ast_program>(new ast_program(/*TODO args*/));
    while (begin++ != end) {
      switch (begin->type()) {
      default:
        return nullptr;
      }
    }
    return nullptr;
  }

  std::unique_ptr<ast_sequence> parse_sequence(token_list_iterator begin, const token_list_iterator end) const {
    if (std::distance(begin, end) <= 0) return nullptr; // TODO: add logging mechanism that dumps errors at end of compilation
    if (begin->type() != token_type::kOPENING_DELIMITER) return nullptr;
    if (begin->value() != "{") return nullptr;
    std::unique_ptr<ast_sequence> sequence(new ast_sequence());
    while (begin++ != end) { // sequence must look like { code }
      if (begin->type() == token_type::kCLOSING_DELIMITER && begin->value() == "}") { return sequence; }

      // switch(it->type()) {
      //   case kNUMBER:
      //   {
      //
      //   }
      //   case kCHAR_LITERAL:
      //   {}
      //   case kSTRING_LITERAL:
      //   {}
      //   case kOPENING_DELIMITER:
      //   {}
      //   case kCLOSING_DELIMITER:
      //   {}
      //   case kTERMINATOR:
      //   {}
      //   case kSEPARATOR:
      //   {}
      //   case gKEYWORDS.at(_value):
      //   {}
      //   case kOPERATOR:
      //   {}
      //   case kPOSSIBLE_ENTITY:
      //   {}
      //   case kERROR:
      //   {}
      //   default:
      //   {}
      //   break;
    }
    return nullptr;
  }
public:
  std::unique_ptr<ast_program> parse(const std::list<token>& tokens) const {
    //TODO: can this be better?
    return parse(std::move(tokens));
  }
  std::unique_ptr<ast_program> parse(std::list<token>&& tokens) const {
    // find a non-kPOSSIBLE_ENTITY token and then read until reach a kPOSSIBLE_ENTITY
    // the set of tokens should make up an expression...
    auto begin = tokens.begin();
    auto end = tokens.end();
    std::cerr << "Parsing..." << std::endl;
    // make expression
    return parse_program(begin, end);
    // need to keep track of imports manually...
    // so need to use the scope objects to hold objects/functions
    // then need to see if have to build imported file
    // NOTE: should not have any issues with naming conflicts across files since using import as or using namespace is not allowed
  }
}; // class parser

} // namespace syntax
