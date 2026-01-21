# ZinDict 项目结构

## 一、Project 目录结构
```
zindict/
├── data/               # 离线词典目录
│  └── dict.db          # 离线词典数据库
│
├── docs/               # 文档目录
│
├── lib/                # 链接库目录（CMake 构建产物）
│
├── scripts/            # 原编译脚本目录（废弃）
│
├── src/                # 源文件目录
│
├── third_party/        # 第三方库目录（C/C++ 源代码）
│
└── README.md           # 项目说明文件
```

## 二、Release 目录结构
以 Windows 系统为例，Release 目录结构如下：
```
zindict-v${version}-${date}-${os_name}-${processor_arch}-${compiler}/
├── README.md               # 项目说明文件
│
├── bin/
│  ├── zindict.exe          # 可执行文件
│  ├── libzindict.rlib      # Rust Library 特定静态中间库格式
│  └── zindict.toml         # 运行时配置文件
│
├── data/
│  └── dict.db              # 离线词典数据库
│
└── docs/
    ├── build.md            # 构建说明文档
    ├── config_example.toml  # 默认运行时配置文件示例
    └── dict.txt            # 用户使用手册
```
