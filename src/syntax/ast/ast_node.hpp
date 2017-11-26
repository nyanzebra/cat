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

  virtual void print() = 0;
};

} // namespace syntax
