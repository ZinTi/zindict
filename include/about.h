/*----------------------------------(一) 引入头文件--------------------------------------------*/
#include <stdio.h>
#include <string.h>
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #include <libgen.h> // for dirname
#endif

/**
 * @brief 宏常量
 * 
 */
#define PROJ_NAME       "ZinDict"
#ifdef _WIN32
    #define PROJ_VER        "0.1.1-WinNT"
#else
    #define PROJ_VER        "0.1.1-GNU/Linux"
#endif
#define PROJ_YEARS      "2023-2025"
#define AUTHOR          "Mr. ZENG Lai"
#define CONTACT         "vip201@126.com"
#define COMPILED        "(compiled "__TIME__", "__DATE__")"

#define USER_MANUAL  "\n\
=== 用户手册(zh-CN) ===\n\
（1）参数模式\n\
运行程序时指定参数，程序执行后即结束。使用格式：\n\
    dict [参数1 参数2 …… 参数n]\n\
参数是你需要翻译的单词或词组，命令行以空格作为分割参数的依据，你可以使用直引号将含有空格的词组扩起来，或使用通配符 _ 代替空格。使用示例：\n\
    dict \'such as\' \"such as\" such_as\n\
\n\
（2）交互模式\n\
未指定参数将进入交互模式。交互模式下，以符号“.”或“:”为首的字符串被认定为内建命令而执行，以“?”为首的字符串则是查询该命令的功能。\n\
所有命令的列表（大小写不敏感）：\n\
    help, manual    获取用户使用手册\n\
    clear, cls          清屏\n\
    exit, quit, e, q          离开交互模式\n\
    prompt  [NewPrompt> ] 修改交互模式下的提示符\n\
\n\
例如：\n\
    Eng> :prompt DICT> ^M\n\
    DICT> \n\
   （此处的 ^M 代指键盘上的 <ENTER> 键）\n\
\n\
交互模式下，将整行字符串都当做查询内容，因此不支持命令行模式那种可以一次查询多个单词或词组的用法。并且不要使用直引号将含有空格的词组括起来，因为程序会将直引号当做单词或词组的组成部分。\n\
\n\
（3）近似匹配\n\
支持使用通配符 %% 和 _ 模糊匹配单词或词组，参数模式和交互模式下都支持。\n\
%% 通配符表示零个或多个字符。例如，word%% 匹配词典中以 word 开头的任何单词或词组。\n\
_ 通配符表示一个字符。例如，_ache 匹配词典中首字母任意，以 ache 结尾的任何单词。\n\
\n\
\n\
\n\
=== User Manual(en-US) ===\n\
(1) Parameter Mode\n\
Specify parameters when running the program, and the program will exit after execution. Usage format:\n\
    dict [param1 param2 ... paramN]\n\
The parameters are the words or phrases you want to translate. Parameters are separated by spaces in the command line. You can use single quotes to enclose phrases containing spaces, or use the wildcard _ to replace spaces. Example:\n\
    dict \'such as\' \"such as\" such_as\n\
\n\
(2) Interactive Mode\n\
If no parameters are specified, the program will enter interactive mode. In interactive mode, any string starting with . or : is treated as a built-in command. A string starting with ? queries the function of the command.\n\
List of all commands (case-insensitive):\n\
    help, manual     Get the user manual\n\
    clear, cls     Clear the screen\n\
    exit, quit     Exit interactive mode\n\
    prompt [NewPrompt>]     Change the prompt in interactive mode\n\
\n\
For example:\n\
    Eng> :prompt DICT> ^M\n\
    DICT>\n\
(Here, ^M represents the <ENTER> key on the keyboard)\n\
\n\
In interactive mode, the entire input line is treated as a query, so you cannot query multiple words or phrases at once like in parameter mode. Do not use single quotes to enclose phrases with spaces, as the program will treat the quotes as part of the word or phrase.\n\
\n\
(3) Approximate \n\
Wildcard symbols %% and _ are supported for fuzzy matching of words or phrases, both in parameter mode and interactive mode.\n\
\n\
%% wildcard represents zero or more characters. For example, word%% matches any word or phrase in the dictionary that starts with \"word\".\n\
_ wildcard represents a single character. For example, _ache matches any word in the dictionary that ends with \"ache\" and starts with any single character.ample, `_ache` matches any word in the dictionary that ends with \"ache\" and starts with any single character.\n\
\n\
"

/**
 * @brief 打印帮助文档，查找命令帮助。
 * @param mPath 离线手册的文件路径
 * @param qStr 需要查询的字符串
 * @return 返回值void
 */
void Help(const char* mPath, const char* qStr);

/**
 * @brief 显示软件的名称、版本、版权等相关信息
 */
void About(void);

/**
 * @brief 设置程序主目录为可执行文件所在目录的父目录
 * @param homePath 保存路径的容器，请事先分配好内存
 * @return 如果成功返回 0
 */
int SetHomePath(char* homePath);
