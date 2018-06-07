#include "syntax/ast.hpp"
#include "syntax/parser.hpp"
#include "syntax/preprocessor.hpp"
#include "syntax/lexer.hpp"
#include "syntax/ast_visitors.hpp"

#include "deps/std.hpp"
#include "utility/exports.hpp"

#define MIN_ARGS 5

/*
  The format should look like:
  meow -o ouput -i input(s)
*/
int main(int argc, char const *argv[]) {
  if (argc < MIN_ARGS) {
    std::cout << "Too few arguments for cat compiler 'meow'" << std::endl;
    return 1;
  }

  std::map<std::string, std::string> input_map;
  for (auto i = 0u; i < MIN_ARGS; ++i) {
    if (argv[i][0] == '-') {
      input_map.emplace(argv[i], argv[i + 1]);
    }
    std::cout << "index: " << i << ", " << argv[i] << std::endl;
  }

  if (input_map.find("-i") == input_map.end()) {
    std::cout << "Must supply input for compiler" << std::endl;
    return 1;
  }

  if (input_map.find("-o") == input_map.end()) {
    std::cout << "Must supply output for compiler" << std::endl;
    return 1;
  }

  syntax::preprocessor pp;
  std::string input = input_map["-i"];
  std::string output = input_map["-o"];
  std::string flag = std::string(argv[0]);
  std::list<std::string> inputs;
  std::string temp = "";
  for (auto i = 0u; i < input.size(); ++i) {
    char c = input[i];
    if (c == ' ') {
      inputs.push_back(temp);
    } else {
      temp += c;
    }
  }
  if (!temp.empty()) inputs.push_back(temp);

  //std::list<std::string> temps = pp.process(std::move(inputs));

  syntax::lexer l;
  l.lex(std::move(inputs));
  if (l.tokens().empty()) return 1;
  std::cout << "lexed input" << std::endl;
  for (auto& tok : inputs) {
    std::cout << tok << ',';
  }

  syntax::parser p;
  auto program = p.parse(l.tokens());
  if (!program) return 1;
  std::cout << "parsed tokens" << std::endl;
  std::cout << "Verify:\n";
  program->print(std::cout, 0);

  // ast and code generation
  syntax::code_generator_visitor visitor;
  std::cout << "init compiling" << std::endl;
  visitor.initialize();
  std::cout << "compiling" << std::endl;
  visitor.create_compile_units(inputs);
  std::cout << "compiling units" << std::endl;
  program->accept(&visitor, {""});
  std::cout << "finalize compiling" << std::endl;
  visitor.finalize(output);
  std::cout << "finished compiling" << std::endl;

  return 0;
}
