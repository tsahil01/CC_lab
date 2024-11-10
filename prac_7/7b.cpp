#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/raw_ostream.h"
#include <iostream>
#include <string>
#include <memory>
#include <vector>

using namespace llvm;

int main() {
    // Step 1: Initialize LLVM Context and Module
    LLVMContext context;
    auto module = std::make_unique<Module>("ArithmeticModule", context);

    // Step 2: Define the function signature (int func(int, int))
    std::vector<Type*> funcArgs(2, Type::getInt32Ty(context)); // Two int32 arguments
    FunctionType* funcType = FunctionType::get(Type::getInt32Ty(context), funcArgs, false);
    Function* function = Function::Create(funcType, Function::ExternalLinkage, "arithmetic", *module);

    // Step 3: Create an entry block for the function
    BasicBlock* entry = BasicBlock::Create(context, "entry", function);
    IRBuilder<> builder(entry);

    // Step 4: Get function arguments
    Function::arg_iterator args = function->arg_begin();
    Value* x = args++;
    x->setName("x");
    Value* y = args++;
    y->setName("y");

    // Step 5: Create arithmetic expressions (e.g., x + y * (x - y))
    Value* sub = builder.CreateSub(x, y, "subtmp");       // (x - y)
    Value* mul = builder.CreateMul(y, sub, "multmp");     // y * (x - y)
    Value* result = builder.CreateAdd(x, mul, "addtmp");  // x + y * (x - y)

    // Step 6: Return the result
    builder.CreateRet(result);

    // Step 7: Validate the generated code
    verifyFunction(*function);

    // Step 8: Output the generated LLVM IR
    module->print(outs(), nullptr);

    return 0;
}
