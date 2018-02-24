#pragma once

#include "ast_node.hpp"

namespace syntax {

class ast_program final : public ast_node {
private:

protected:
public:
private:
protected:
public:
  virtual std::ostream& print(std::ostream& stream, size_t tabs = 0) { return stream; }
}; // contains compilation nodes

} // namespace syntax
