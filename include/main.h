#ifndef INC_MAIN_H
#define INC_MAIN_H

/*------------------（一） 包含库和项目头文件 -----------------------*/
// 1.1、标准库
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

// 1.2、平台库
#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #include <libgen.h> // for dirname
#endif

// 1.3、第三方库
#include <sqlite3.h>

// 1.4、项目其他头文件
#include "color.h"


/*------------------（二） 定义项目宏常量 -----------------------*/

#define MAX_SIZE_OF_SQL                     200
#define MAX_SIZE_OF_WORD                    100
#define DEFAULT_PROMPT                      "Eng> "

/*------------------（三） 全局变量与定义结构体类型 -----------------------*/

/**
 * text: CLI提示符文字
 * color: 结构体TextColor类型，包含两个枚举类型元素——前景色和背景色
 */
typedef struct{
   char text[MAX_SIZE_OF_WORD];
   TextColor color;
}PROMPT;

TextColor defaultColor = {COLOR_BRIGHT_CYAN, COLOR_NONE}; // 浅青字
TextColor invalidColor = {COLOR_BRIGHT_RED, COLOR_NONE}; // 红字
TextColor wordColor = {COLOR_BLUE, COLOR_BRIGHT_YELLOW}; // 0xE1 浅黄底蓝字
TextColor cyanColor = {COLOR_CYAN, COLOR_NONE}; // 0x03 青字
TextColor magentaColor = {COLOR_BRIGHT_MAGENTA, COLOR_NONE}; // 浅紫字
TextColor grayColor = {COLOR_BRIGHT_BLACK, COLOR_NONE}; // 灰字
TextColor greenColor = {COLOR_BRIGHT_GREEN, COLOR_NONE}; // 浅绿字
TextColor lightblueColor = {COLOR_BRIGHT_BLUE, COLOR_NONE}; // 

/*------------------（四） 声明函数原型 -----------------------*/

/**
 * 回调函数：打印查询结果
 * @param data 第一个参数
 * @param argc 参数数量
 * @param argv 参数值数组
 * @param azColName 列名
 * @return 返回值int型
 */
static int ShowResult_callback(void *data, int argc, char **argv, char **azColName);

/**
 * 在词典中查询单词或词组
 * @param word 待查单词
 * @param DB SQLite3数据库路径
 */
int QueryTheWord(const char* word, const char* DB);

#endif