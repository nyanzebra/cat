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

  virtual std::ostream& print(std::ostream& stream, size_t tabs = 0) = 0;
};

} // namespace syntax
