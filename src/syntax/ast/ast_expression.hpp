#pragma once

#include "ast_node.hpp"

namespace syntax {

class ast_expression : public ast_node {
public:
  virtual ~ast_expression() = default;

  virtual void print() = 0;
};

} // namespace syntax
