#ifndef BINHUB_IO_H
#define BINHUB_IO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#if defined(_WIN32) || defined(_WIN64)
	#ifdef _MSC_VER
		#define NOMINMAX
	#endif
	#include <windows.h>
#elif defined(__linux__) || defined(__unix__)
    #include <locale.h>
    #include <langinfo.h>
#else

#endif

// 定义颜色枚举
typedef enum {
    CLR_NONE = -1, // 不设置颜色
    CLR_BLACK = 0, // 黑色
    CLR_RED,       // 红色
    CLR_GREEN,     // 绿色
    CLR_YELLOW,    // 黄色
    CLR_BLUE,      // 蓝色
    CLR_MAGENTA,   // 品红色
    CLR_CYAN,      // 青色
    CLR_WHITE,     // 白色
    CLR_BRT_BLACK, // 亮黑色（灰色）
    CLR_BRT_RED,   // 亮红色
    CLR_BRT_GREEN, // 亮绿色
    CLR_BRT_YELLOW, // 亮黄色
    CLR_BRT_BLUE,  // 亮蓝色
    CLR_BRT_MAGENTA, // 亮品红色
    CLR_BRT_CYAN,    // 亮青色
    CLR_BRT_WHITE,    // 亮白色
    CLR_RESET // 默认颜色（重置）
} binhub_ansi_color_t; // ansi color

#define CLR_GRAY CLR_BRT_BLACK // 灰色

// fg 不能为 CLR_NONE, 请使用 CLR_RESET
typedef struct binhub_tcolor_t{ // text color
    binhub_ansi_color_t fg; // 前景色
    binhub_ansi_color_t bg; // 背景色
} binhub_tcolor_t;

// 定义编码类型枚举
enum binhub_console_encoding_t {
    ENCODING_GBK,
    ENCODING_UTF8
};

// 添加颜色初始化的兼容宏
#ifdef __cplusplus
    // C++11及更高版本
    #define BINHUB_COLOR_INIT(fg, bg) binhub_tcolor_t{fg, bg}
#else
    // C99复合字面量
    #define BINHUB_COLOR_INIT(fg, bg) (binhub_tcolor_t){fg, bg}
#endif

/**
 * @brief 彩色格式化打印函数
 * @param color 颜色
 * @param format 字符串格式
 * @param ... 其他变量
 * @details 换行符尽量写在 format 字符串末尾，尽量不要写在 ... 变量中
 * @return int 如果成功，则返回写入的字符总数，否则返回一个负数
 */
int binhub_cprintf(binhub_tcolor_t color, const char* format, ...);

/**
 * @brief 打印系统错误信息到 stderr (colorful perror)
 * @param str 错误信息
 */
void binhub_cperror(const char *str);

/**
 * @brief 输出自定义错误信息(custom/colorful error)
 * @param format 格式化字符串
 * @param ... 可变参数列表
 */
void binhub_cerr(const char *format, ...);

/**
 * @brief 输出自定义致命错误信息并终止程序（custom/colorful error - fatal）
 * @param format 格式化字符串
 * @param ... 可变参数列表
 */
void binhub_cerr_f(const char *format, ...);

/**
 * @brief 输出自定义警告信息（custom/colorful warn）
 * @param format 格式化字符串
 * @param ... 可变参数列表
 */
void binhub_cwarn(const char *format, ...);

/**
 * @brief 修改命令行颜色
 * @param color 颜色
 */
void binhub_chcolor(binhub_tcolor_t color);

/**
 * @brief win32 控制台颜色属性（ BF, 背景色;前景色 ）映射为 binhub_tcolor_t 类型（ 前景色;背景色 ）
 * @param win32_color_attr win32 颜色属性
 */
binhub_tcolor_t binhub_win_attr_to_tcolor(uint8_t win32_color_attr);

/**
 * @brief 设置控制台编码
 * @param encoding 编码类型：ENCODING_GBK 或 ENCODING_UTF8
 * @return int 成功返回0，失败返回非0错误码
 */
int binhub_setenc(enum binhub_console_encoding_t encoding);

/**
 * @brief 猜测数据的字符集编码是否为 UTF-8 格式
 * @param data 判断目标
 * @param len 数据长度
 * @return 如果返回值为 true 代表可能是 UTF-8 ，如果为 false 代表不太可能为 UTF-8
 */
bool is_data_utf8(const char* data, int len);

/**
 * @brief 根据目标源文件自动选择活动代码页 CodePage
 * @param filename 目标文件名
 * @return
 */
int binhub_setcp_auto(const char* filename);

/**
 * @brief 进度条动画-转圈
 * @param text 文本提示
 * @param style 风格
 */
void load_loop(const char* text, int style);

/**
 * @brief 清屏（包括可视区域 viewport，和滚动缓冲区 scrollback buffer）
 * @return bool 成功返回true，失败返回false
 */
bool binhub_clear_screen();

#ifdef __cplusplus
}
#endif

#endif
