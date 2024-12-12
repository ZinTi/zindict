#!/bin/bash

# 获取当前脚本所在的目录
SCRIPT_DIR=$(cd "$(dirname "$0")" && pwd)

# 设置项目根目录为脚本所在目录的父目录
ROOT_DIR=$(dirname "$SCRIPT_DIR")

# 设置输出目录
OUTPUT_DIR="$ROOT_DIR/bin"

# 如果输出目录不存在，则创建
if [ ! -d "$OUTPUT_DIR" ]; then
  mkdir -p "$OUTPUT_DIR"
fi

# 编译源文件并输出到指定目录
gcc -I"$ROOT_DIR/include" -I"$ROOT_DIR/third_party/sqlite-3.50.0/include" "$ROOT_DIR/src/"*.c -o "$OUTPUT_DIR/dict" -Os -L"$ROOT_DIR/third_party/sqlite-3.50.0/lib/linux_x86_64" -lsqlite3
if [ $? -ne 0 ]; then
  echo "编译失败，请检查源文件是否存在以及语法是否正确。"
  exit 1
fi

# 显示输出文件
if [ -f "$OUTPUT_DIR/dict" ]; then
  ls -l "$OUTPUT_DIR/dict"
else
  echo "目标文件未生成，请检查编译步骤。"
fi

