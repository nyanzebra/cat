#include "syntax/ast.hpp"
#include "syntax/parser.hpp"
#include "syntax/preprocessor.hpp"
#include "syntax/lexer.hpp"
#include "llvm/llvm.hpp"

#include <iostream>
#include <string>
#include <list>

#define MIN_ARGS 4

/*
  The format should look like:
  meow -o ouput -i input(s)
*/
int main(int argc, char const *argv[]) {

  if (argc < MIN_ARGS) {
    std::cout << "Too few arguments for cat compiler 'meow'" << std::endl;
    return 1;
  }

  preprocessor pp;
  std::string output = "output";
  std::string flag = std::string(argv[0]);
  std::list<std::string> inputs;

  if (flag == "-o"s) {
    output = std::string(argv[0]);
    for (auto i = 3; i < argc; ++i) {
      inputs.push_back(argv[i]);
    }
  } else if (flag == "-i"s) {
    output = std::string(argv[argc - 1]);
    for (auto i = 1; i < argc - 2; ++i) {
      inputs.push_back(argv[i]);
    }
  } else {
    std::cout << "Must have output and input flags for compilation" << std::endl;
    return 1;
  }

  std::list<std::string> temps = pp.process(inputs);

  lexer l;
  l.lex(temps);


  parser p;
  p.parse(l.tokens());

  // ast and code generation


  return 0;
}
