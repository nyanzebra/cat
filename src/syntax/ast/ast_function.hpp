#pragma once

#include "ast_function_prototype.hpp"
#include "ast_block.hpp"

namespace syntax {

class ast_function : public ast_expression {
private:
  std::unique_ptr<ast_function_prototype> _prototype;
  std::unique_ptr<ast_block> _body;
protected:
public:
private:
protected:
public:
  ast_function(std::unique_ptr<ast_function_prototype> prototype, std::unique_ptr<ast_block> body) : _prototype(std::move(prototype)), _body(std::move(body)) {}

  std::ostream& print(std::ostream& stream, size_t tabs = 0) override {
    indent(stream, tabs);
    _prototype->print(stream);
    stream << " "; // format
    _body->print(stream, tabs);
    return stream;
  }

  const std::unique_ptr<ast_function_prototype>& prototype() const { return _prototype; }
  const std::unique_ptr<ast_block>& body() const { return _body; }

  void* accept(code_generator_visitor* visitor, const scope& current_scope) override;
};

} // namespace syntax
