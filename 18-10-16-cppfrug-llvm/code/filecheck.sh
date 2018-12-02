#!/bin/bash
#

set -ex

clang++-4.0 -Xclang -load -Xclang $HOME/dev/llvm-intptrcleanup/build_release/IntPtrCleanup.so -O2 -S -emit-llvm -o /tmp/a.ll op_zip_iterator.cpp -std=c++11
#clang++-4.0 -O2 -S -emit-llvm -o /tmp/a.ll op_zip_iterator.cpp -std=c++11
~/dev/llvm-5/build_release_shared_rtti/bin/FileCheck op_zip_iterator.cpp </tmp/a.ll
clang++-4.0 -O2 /tmp/a.ll -c -o /tmp/a.o
