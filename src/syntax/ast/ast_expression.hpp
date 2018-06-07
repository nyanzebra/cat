#pragma once

#include "ast_node.hpp"

namespace syntax {

class ast_expression : public ast_node {
protected:
  void indent(std::ostream& stream, size_t tabs) {
    for (auto i = 0u; i < tabs; ++i) {
      stream << '\t';
    }
  }
public:
  virtual ~ast_expression() = default;
};

} // namespace syntax
