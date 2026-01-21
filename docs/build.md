# 构建说明

## 一、环境准备
构建需要以下工具：
```
CMake
C/C++ 编译器
Rust 工具链（rustc, cargo）
```

C/C++ 编译器有不同的选择，请确保安装的编译器版本与你使用的 Rust 环境版本保持一致。（以下版本仅针对 AMD64 架构的 Windows 系统和 Linux 系统）

1. Windows 系统  
> 最主流的 C/C++ 编译器包括 `MSVC` 和 `MinGW-w64` 。
```
若使用 MinGW-w64，请安装 `x86_64-pc-windows-gnu` 版本 Rust；
若使用 MSVC，请安装 `x86_64-pc-windows-msvc` 版本 Rust；
若使用 LLVM，请安装 `x86_64-pc-windows-gnullvm` 版本 Rust。
```

2. Linux 系统  
> 最主流的 C/C++ 编译器包括 `GCC` 和 `Clang` 。
```
参考官方文档安装 Rust 环境。
```


3. 其他系统  
```
macOS，FreeBSD，OpenBSD 等系统请参考官方文档安装 Rust 环境。
```

## 二、静态库构建

项目构建流程：
```
1. 处理对 C 语言库的依赖，cmake 命令构建静态库；
2. cargo 命令构建 Rust 项目，链接 C 语言静态库；
```
本部分内容聚焦 C 语言静态库的构建。

1. Windows 系统

> 使用 MSVC 编译器（Visual Studio）编译的 C/C++ 静态库命名为 `xxx.lib`；  
> 使用 GCC 编译器（MinGW-w64）编译的 C/C++ 静态库命名为 `libxxx.a`，与 Linux 类似；

2. Linux 系统

> C/C++ 静态库命名为 `libxxx.a`；

C 语言第三方库依赖如下：  
1. [BinHub](https://github.com/zinti/binhub/tree/main/lib)  
   用于输出 ANSI 颜色（Windows 平台使用原生API，确保兼容 Windows 10 以下的系统）
2. [SQLite3](https://sqlite.org/download.html)  
   用于读写数据库数据（已由 `rusqlite` 库自动处理，无需手动绑定包装）


## 三、项目构建  
Rust 依赖见 Cargo.toml 所列；  

构建命令参考项目根目录下的 `build-${os_name}-${compiler}` 脚本，
参考脚本：
- [Windows + MinGW-w64](../build-windows-mingw.bat)
- [Windows + MSVC](../build-windows-msvc.bat)
- [Linux + GCC](../build-linux-gcc.sh)
- [Linux + Clang](../build-linux-clang.sh)

构建命令示例：
```pwsh
# 1. Build dependencies
cmake -S . -B "target/cmake_build" -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
cmake --build "target/cmake_build" --parallel %NUMBER_OF_PROCESSORS%

# 2. Build project
cargo build --release
```