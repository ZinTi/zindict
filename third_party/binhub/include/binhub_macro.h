/**
 * @file binhub_macro.h 宏
 *
 */

#ifndef BINHUB_MACRO_H
#define BINHUB_MACRO_H

#include <stdint.h>
#include "binhub_io.h" // binhub_clear_screen()

/**
 * @brief 打印环境变量
 * @details BINHUB_PRINT_ENV_VAR(var) 打印环境变量 var 的值
 */
#ifdef _WIN32
    #define BINHUB_PRINT_ENV_VAR(var) do { \
        const char* var = getenv( #var ); \
        if(var == (void*)0) { \
            binhub_cprintf(BINHUB_COLOR_INIT(CLR_RED, CLR_NONE), "The environment variable " #var " does not exist!\n"); \
        } else { \
            binhub_cprintf(BINHUB_COLOR_INIT(CLR_BRT_GREEN, CLR_NONE), "${env:" #var "}"); \
            printf(" = "); \
            binhub_cprintf(BINHUB_COLOR_INIT(CLR_CYAN, CLR_NONE), "%s\n", var); \
        } \
    } while(0)
#else
    #define BINHUB_PRINT_ENV_VAR(var) do { \
        const char* var = getenv( #var ); \
        if(var == (void*)0) { \
            binhub_cprintf(BINHUB_COLOR_INIT(CLR_RED, CLR_NONE), "The environment variable " #var " does not exist!\n"); \
        } else { \
            binhub_cprintf(BINHUB_COLOR_INIT(CLR_BRT_GREEN, CLR_NONE), "${" #var "}"); \
            printf(" = "); \
            binhub_cprintf(BINHUB_COLOR_INIT(CLR_CYAN, CLR_NONE), "%s\n", var); \
        } \
    } while(0)
#endif

/**
 * @brief 清屏
 * @details BINHUB_CLEAR_SCREEN 清屏
 */
// #ifdef _WIN32
//     #define BINHUB_CLEAR_SCREEN system("cls")
// #elif defined(__linux__) || defined(__APPLE__)
//     #define BINHUB_CLEAR_SCREEN system("clear")
// #else
//     #define BINHUB_CLEAR_SCREEN
// #endif
#define BINHUB_CLEAR_SCREEN binhub_clear_screen()

/**
 * @brief 带文件和行号的调试日志
 * @details BINHUB_DEBUG_LOG(format, ...) 打印调试日志
 */
#define BINHUB_DEBUG_LOG(format, ...) \
printf("[%s:%d] " format "\n", __FILE__, __LINE__, ##__VA_ARGS__)

/**
 * @brief 换行
 * @details BINHUB_ENDLINE(var) 换行
 */
#define BINHUB_ENDLINE(var) do { \
    for(unsigned int i = 0; i < var ; i++) putchar('\n'); \
} while(0)

/**
 * @brief 忽略警告, 未使用变量
 * @details BINHUB_UNUSED(x) 未使用变量
 */
#define BINHUB_UNUSED(x) (void)(x)


/////////////////////////////////////////////////////////////////

#endif /* BINHUB_MACRO_H */
