#pragma once

#include "ast_conditional.hpp"
#include "syntax/scope.hpp"

namespace syntax {

class ast_while final : public ast_conditional {
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
