#pragma once

#include "ast_node.hpp"

namespace syntax {

class ast_expression : public ast_node {
protected:
  void indent(size_t tabs) {
    for (auto i = 0u; i < tabs; ++i) {
      std::cout << '\t';
    }
  }
public:
  virtual ~ast_expression() = default;

  virtual void print(size_t tabs) = 0;
};

} // namespace syntax
