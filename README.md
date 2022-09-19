# newPM_LLVM_pass
A HelloWorld LLVM pass that uses New Pass Manager

## Why?
During my work with LLVM I found out that implementing LLVM pass using New Pass Manager is still not quite straight-forward (at least in 2022). There are tutorials that tells you how to create a simple static LLVM pass (where we embed our pass in the LLVM code), very few articles about how to build LLVM pass as a shared library, almost no info about running this as a plugin from clang (mostly people load it to opt). In order to avoid future struggling, here is the example implementation of a HelloWorld LLVM pass that will do some prints to `errs()` and `dbgs()` (using `-debug-only` flag).

## How?
To build and test this pass:
 - Clone the repository
 - Go to the repository directory and run command `mkdir build`
 - Go to the build directory (`cd build`)
 - Run cmake command: `cmake ..`
 - Build the pass: `make`
 Now in `/path/to/repo/build/source` there should be a `.so` file. This is your LLVM pass.
 
 To load it with opt: `opt -O0 -load-pass-plugin /path/to/repo/build/source/libHelloWorldPass.so -debug-only dump-world -S before.ll -o after.ll`
 
 To load it with clang: `clang -Xclang -disable-O0-optnone -O0 -fpass-plugin=/path/to/repo/build/source/libHelloWorld.so -mllvm -debug-only=dump-trace source.cpp`
 
## Misc
Make sure that you have only one version of LLVM being installed. If not, take into attention the path to clang and opt that you use (should be visible as environmental variables). You can work with a specific LLVM installation, in this case, modify the /CMakeFiles.txt `include_directories` and `link_directories` fields. The first one should have two paths to the include directory of LLVM (`~/llvm/include` and `~/build/include`); the last one should have the path to the library directory (`~/llvm/lib`).

This LLVM pass is a Module Pass that is running before all other optimizations (it's regulated by the `PassBuilder::registerOptimizerEarlyEPCallback`). For any other ways of registering a callback, take a look at [LLVM documentation](https://llvm.org/doxygen/classllvm_1_1PassBuilder.html#a5ac5d2f0e7a33e8ba20e5f7f28f60791)
