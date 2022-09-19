//===-- HelloWorld.cpp - Example Transformations --------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "HelloWorld.h"

#include "llvm/Passes/PassPlugin.h"
#include "llvm/Passes/PassBuilder.h"

using namespace llvm;

#define DEBUG_TYPE "dump-world"

PreservedAnalyses HelloWorldPass::run(Module &M,
                              ModuleAnalysisManager &MAM) {
    for (Function &F : M) { 
        errs() << "Hello World!\n";
        errs() << F.getName() << "\n";
    }
   
    LLVM_DEBUG(dbgs() << "Running under debug flag\n");
    return PreservedAnalyses::all();
}
//-----------------------------------------------------------------------------
// New PM Registration
//-----------------------------------------------------------------------------
llvm::PassPluginLibraryInfo getHelloWorldPassPluginInfo() {
  return {LLVM_PLUGIN_API_VERSION, "hello-world-pass", LLVM_VERSION_STRING,
          [](PassBuilder &PB) {
            PB.registerOptimizerEarlyEPCallback(
                [](ModulePassManager &MPM, OptimizationLevel ) {
                  MPM.addPass(HelloWorldPass());
                  return true;
                });
          }};
}

extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo
llvmGetPassPluginInfo() {
  return getHelloWorldPassPluginInfo();
}
