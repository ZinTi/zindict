#!/usr/bin/env bash
# 1. Build dependencies
cmake -S . -B "target/cmake_build" -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
cmake --build "target/cmake_build" --parallel ${NUMBER_OF_PROCESSORS}
rm -f zindict-v*/bin/* # binhub example

# 2. Build project
cargo build --release

# 3. Move executable to target directory
mv target/release/zindict zindict-v*/bin/
mv target/release/*.rlib zindict-v*/bin/
ls -al .
cp -R data/ zindict-v*/
cp -R docs/ zindict-v*/
cp LICENSE zindict-v*/
cp README.md zindict-v*/
