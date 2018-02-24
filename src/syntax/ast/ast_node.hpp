#pragma once

namespace syntax {

class ast_node {
private:
protected:
public:
private:
protected:
public:
  virtual ~ast_node() = default;

  virtual std::ostream& print(std::ostream& stream, size_t tabs = 0) = 0;
};

} // namespace syntax
