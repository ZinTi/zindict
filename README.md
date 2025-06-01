# 📕 ZinDict 

**ZinDict** 是一个轻量级的离线词典CLI程序，旨在提供快速、简便的英语单词查询体验。支持在 Windows 和 Linux 上运行。  

## （一）功能
- 查询单词的英汉翻译
- 离线运行，无需网络支持
- 跨平台支持 Windows 和 Linux

---

## （二）安装与使用

### （2.1）Windows 安装
1. 将 `zindict/bin/` 目录添加到系统的环境变量中。
2. 或者在任意一个已经在环境变量中的目录中创建一个名为 `dict.bat` 的脚本，内容如下：  
   ```bat
   zindict/bin/dict.exe %*
   ```
3. 运行命令 `dict` 使用词典程序。

### （2.2）Linux 安装
1. 将整个项目复制到 `/opt/` 目录下：  
   ```bash
   sudo cp -r zindict /opt/
   ```
2. 新建一个 alias 指向词典程序：  
   ```bash
   echo "alias dict='/opt/zindict/bin/dict'" >> ~/.bashrc
   source ~/.bashrc
   ```
3. 运行命令 `dict` 使用词典程序。

---

## （三）使用示例
在终端或命令提示符中运行以下命令：  
```bash
dict word _ord word%
```
输出查询结果，下划线_代表单个字母，百分号%代表多个字母。
```bash
dict
```
如果输入命令时，不输入参数则进入交互模式。交互模式使用 `.exit` 或 `.quit` 退出，使用 `.help` 或 `.manual` 获取使用帮助，使用 `.cls` 或 `.clear` 清屏，使用 `.prompt [new word]` 更换提示符。

---

## （四）项目目录结构
```
zindict/
├── bin/          # 可执行文件目录（Release）
├── data/         # 离线词典目录
├── docs/         # 使用手册目录
├── include/      # 头文件目录
├── lib/          # 链接库目录
├── scripts/      # 编译脚本目录
├── src/          # 源文件目录
└── README.md     # 项目说明文件
```

---

## （五）许可证
ZinDict 使用 [GPL 许可证](LICENSE)。

---