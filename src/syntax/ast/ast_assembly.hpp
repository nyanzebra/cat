#pragma once

#include "ast_expression.hpp"

namespace syntax {

class ast_assembly final : public ast_expression {
private:
protected:
public:
private:
protected:
public:
  std::ostream& print(std::ostream& stream, size_t tabs = 0) override { return stream; }

  void* accept(code_generator_visitor* visitor) override;
};

} // namespace syntax
