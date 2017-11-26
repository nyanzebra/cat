#pragma once

#include "llvm/include/llvm/ADT/APFloat.h"
#include "llvm/include/llvm/ADT/APInt.h"
#include "llvm/include/llvm/ADT/APSIntt.h"
#include "llvm/include/llvm/ADT/STLExtras.h"
#include "llvm/include/llvm/IR/BasicBlock.h"
#include "llvm/include/llvm/IR/Constants.h"
#include "llvm/include/llvm/IR/DerivedTypes.h"
#include "llvm/include/llvm/IR/Function.h"
#include "llvm/include/llvm/IR/IRBuilder.h"
#include "llvm/include/llvm/IR/LLVMContext.h"
#include "llvm/include/llvm/IR/Module.h"
#include "llvm/include/llvm/IR/Type.h"
#include "llvm/include/llvm/IR/Verifier.h"

namespace llvm {

enum class llvm_type : char {
  kNONE,
  kVALUE,
  kFUNCTION,
};

class code_generator {
private:
  LLVMContext _context;
  IRBuilder<> _builder;
  std::unique_ptr<Module> _module;
  scope _scope;
protected:
public:
private:
protected:
public:
  template<typename T>

}; // class code_generator

} // namespace llvm
