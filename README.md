# 📕 ZinDict 

**ZinDict** 是一个轻量级的英汉离线词典程序，旨在提供快速、简便的、命令行中的英语单词查询体验。支持在 Windows 和 Linux 上运行。 REPL 模式下支持实时显示。 

![example.png](./docs/img/example.png "示例")

## 一、功能
- 查询英语单词的汉语翻译
- 离线运行，无需网络支持
- 跨平台支持 Windows 和 Linux

---

## 二、构建
> 本项目需要依赖 C 语言编译的库，需要预先安装 C/C++ 开发环境并编译 C 库。

项目结构和 Release 目录结构参见 [目录文档](docs/directories.md)，构建说明参见 [构建文档](docs/build.md)

---

## 三、安装与使用

### 3-1. Windows 安装
1. ***添加环境变量***  
   将 `zindict/bin/` 目录添加到系统的环境变量中；步骤如下：
   ```txt
   Win+R -> 输入 `sysdm.cpl` -> 点击 `环境变量` -> 点击 `系统变量` -> 点击 `Path` -> 编辑 -> 新增 `zindict/bin/` 目录 -> 确定
   ```

   或者在任意一个已经在环境变量中的目录中创建一个名为 `dict.bat` 的脚本，内容如下：  
   ```bat
   @REM Full path of zindict.exe + %*
   "D:/app/zindict-v*.*.*-windows-amd64-gnu/bin/zindict.exe" %*
   ```

   第二种方法适用于不想编辑 `Path` 环境变量的情况，注意将 cmd 批处理脚本中的 *可执行文件的路径* 替换成实际安装路径。

2. ***修改配置文件（可选）***  
   > 首次运行时，程序会自动在 `zindict.exe` 所在目录下创建 `zindict.toml` 配置文件。若需要自定义配置，可修改 `zindict.toml` 文件；若无此需求，可以忽略此步骤。  

   编辑 `bin/zindict.toml` 文件配置 `dict.db` 文件路径和 `history.txt` 文件路径；  
   完整内容参考 [配置文件示例](./docs/config_example.toml)
   ```toml
   [database]
   # The path to the dictionary database file.
   path = "D:/app/zindict-v*.*.*-20YYMMDD-windows-amd64-mingw/data/dict.db" # 关键配置
   main_table = "iciba"

   [readline.history]
   enable = true
   # The path to the readline history file.
   path = "D:/app/zindict-v*.*.*-20YYMMDD-windows-amd64-mingw/data/history.txt" # 关键配置
   max_size = 200

   # ...... 其他配置
   ```

3. ***测试结果***  
   运行命令 `dict` 或 `dict.bat` 使用词典程序。

### 3-2. Linux 安装
1. ***移动目录***  
   将整个项目复制到 `/opt/` 目录下：  
   ```bash
   sudo cp -r zindict /opt/
   ```
   
2. ***新增 alias***  
   在 `~/.bashrc` 中新建一个 alias 指向词典程序：  
   命令行快速追加到 `~/.bashrc` 中：
   ```bash
   echo "alias dict='/opt/zindict-v*.*.*-linux-x86_64-gnu/bin/zindict'" >> ~/.bashrc
   source ~/.bashrc
   ```
   或手动编辑 `~/.bashrc` 内容：
   ```bash
   # https://github.com/ZinTi/zindict
   alias dict='/opt/zindict-v*.*.*-linux-x86_64-gnu/bin/zindict'
   ```
   然后执行 `source ~/.bashrc` 命令。

3. ***修改配置文件（可选）***  
   > 首次运行时，程序会自动在 `zindict` 所在目录下创建 `zindict.toml` 配置文件。若需要自定义配置，可修改 `zindict.toml` 文件；若无此需求，可以忽略此步骤。  

   编辑 `zindict.toml` 文件配置 `dict.db` 文件路径和 `history.txt` 文件路径；  
   参考 [配置文件示例](./docs/config_example.toml)，类同前述 Windows 安装配置方法。

4. ***测试结果***  
   运行命令 `dict` 使用词典程序。

---

## 四、使用示例
在终端或命令提示符中运行以下命令：  
```bash
dict word _ord word%
```
输出查询结果，下划线_代表单个字母，百分号%代表多个字母。
```bash
dict
```
如果输入命令时，不输入参数则进入交互模式。交互模式使用 `.exit` 或 `.quit` 退出，使用 `.help` 或 `.manual` 获取使用帮助，使用 `.cls` 或 `.clear` 清屏，使用 `.prompt [new word]` 更换提示符。或可使用 `:` 字符替代 `.` 字符。

---

## （五）许可证
ZinDict 使用 [GPL-3.0 许可证](LICENSE)。

---