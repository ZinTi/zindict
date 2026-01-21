#!/bin/zsh
# 1. Build dependencies
cmake -S . -B "target/cmake_build" -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
cmake --build "target/cmake_build" --parallel $(sysctl -n hw.ncpu)
rm -f zindict-v*/bin/* # binhub example

# 2. Build project
cargo build --release

# 3. Move executable to target directory
mv target/release/zindict zindict-v*/bin/
mv target/release/*.rlib zindict-v*/bin/
ls -al .
# zsh 中 源目录不要有尾随斜杠，否则不会复制源目录本身
cp -R data zindict-v*/
cp -R docs zindict-v*/
cp LICENSE zindict-v*/
cp README.md zindict-v*/
