//===-- HelloWorld.h - Example Transformations ------------------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_HELLOWORLD_H
#define LLVM_HELLOWORLD_H

#include "llvm/IR/PassManager.h"
#include "llvm/Pass.h"

#include "llvm/Support/Debug.h"
namespace llvm {

class HelloWorldPass : public PassInfoMixin<HelloWorldPass> {
public:
  PreservedAnalyses run (Module &M, ModuleAnalysisManager &MAM);
};

} // namespace llvm

#endif // LLVM_HELLOWORLD_H
