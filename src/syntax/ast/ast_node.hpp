#pragma once

#include "deps/std.hpp"
#include "syntax/scope.hpp"

namespace syntax {

class code_generator_visitor;

class ast_node {
private:
protected:
public:
private:
protected:
public:
  virtual ~ast_node() = default;

  virtual std::ostream& print(std::ostream& stream, size_t tabs = 0) = 0;

  virtual void* accept(code_generator_visitor* visitor, const scope& current_scope) = 0;
};

} // namespace syntax
