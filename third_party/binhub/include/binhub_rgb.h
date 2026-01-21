/**
 * @file binhub_rgb.h
 * @brief struct binhub_rgb_t
 */

#ifndef BINHUB_RGB_H
#define BINHUB_RGB_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

// 定义分量默认运算的宏
#define BINHUB_RGB_ADD(a, b, c) binhub_rgb_add_saturate(a, b, c)
#define BINHUB_RGB_SUB(a, b, c) binhub_rgb_sub_saturate(a, b, c)

typedef struct binhub_rgb_t binhub_rgb_t; // 前向声明，不完全类型

typedef enum {
    RGB_FORMAT_CSV,      // "r,g,b"
    RGB_FORMAT_HEX,      // "#RRGGBB"
    RGB_FORMAT_CSS       // "rgb(r, g, b)"
} binhub_rgb_format_t;

/**
 * @name binhub_rgb_t 类型的管理
 * 该组函数用于 binhub_rgb_t 类型的 create, destroy, setter, getter
 * @{
 */

/**
 * @fn binhub_rgb_t* binhub_rgb_new(uint8_t red, uint8_t green, uint8_t blue)
 * @brief binhub_rgb_t constructor
 * @param red 红色分量 0-255
 * @param green 绿色分量 0-255
 * @param blue 蓝色分量 0-255
 * @return 成功返回指向 binhub_rgb_t 对象的指针（>0）
 * @see binhub_rgb_delete
 */

/**
 * @fn binhub_rgb_t* binhub_rgb_new_from_hex(const char* hex_str)
 * @brief binhub_rgb_t constructor
 * @param hex_str "#000000" ~ "#FFFFFF" 格式的十六进制颜色字符串
 * @return 成功返回指向 binhub_rgb_t 对象的指针（>0）
 * @see binhub_rgb_delete
 */

/**
 * @fn void binhub_rgb_delete(binhub_rgb_t* rgb)
 * @brief binhub_rgb_t destructor
 * @param rgb 由 binhub_rgb_new() 返回的指针
 * @see binhub_rgb_new
 */

/**
 * @fn uint8_t binhub_rgb_get_red(const binhub_rgb_t* rgb)
 * @brief 获取 binhub_rgb_t 结构体的 red 分量
 * @param rgb 指向 binhub_rgb_t 对象的指针
 * @return red 分量
 */

/**
 * @fn uint8_t binhub_rgb_get_green(const binhub_rgb_t* rgb)
 * @brief 获取 binhub_rgb_t 结构体的 green 分量
 * @param rgb 指向 binhub_rgb_t 对象的指针
 * @return green 分量
 */

/**
 * @fn uint8_t binhub_rgb_get_blue(const binhub_rgb_t* rgb)
 * @brief 获取 binhub_rgb_t 结构体的 blue 分量
 * @param rgb 指向 binhub_rgb_t 对象的指针
 * @return blue 分量
 */

/**
 * @fn void binhub_rgb_set_red(binhub_rgb_t* rgb, uint8_t red)
 * @brief 设置 binhub_rgb_t 结构体的 red 分量
 * @param rgb 指向 binhub_rgb_t 对象的指针
 * @param red red 分量
 */

/**
 * @fn void binhub_rgb_set_green(binhub_rgb_t* rgb, uint8_t green)
 * @brief 设置 binhub_rgb_t 结构体的 green 分量
 * @param rgb 指向 binhub_rgb_t 对象的指针
 * @param green green 分量
 */

/**
 * @fn void binhub_rgb_set_blue(binhub_rgb_t* rgb, uint8_t blue)
 * @brief 设置 binhub_rgb_t 结构体的 blue 分量
 * @param rgb 指向 binhub_rgb_t 对象的指针
 * @param blue blue 分量
 */

/** @} */ // 结束“binhub_rgb_t 类型的管理”分组

// --- Function Prototype --- //
binhub_rgb_t* binhub_rgb_new(uint8_t red, uint8_t green, uint8_t blue);
void binhub_rgb_delete(binhub_rgb_t* rgb);
uint8_t binhub_rgb_get_red(const binhub_rgb_t* rgb);
uint8_t binhub_rgb_get_green(const binhub_rgb_t* rgb);
uint8_t binhub_rgb_get_blue(const binhub_rgb_t* rgb);
void binhub_rgb_set_red(binhub_rgb_t* rgb, uint8_t red);
void binhub_rgb_set_green(binhub_rgb_t* rgb, uint8_t green);
void binhub_rgb_set_blue(binhub_rgb_t* rgb, uint8_t blue);

/**
 * @name binhub_rgb_t 的基本运算操作
 * @{
 */

/**
 * @fn char* binhub_rgb_to_string(const binhub_rgb_t* rgb, binhub_rgb_format_t format, char* buffer, size_t buffer_size)
 * @brief 转换为字符串
 * @param rgb 指向 binhub_rgb_t 对象的指针
 * @param format 字符串格式
 * @param buffer 接收数据的缓冲区
 * @param buffer_size 缓冲区字节数
 * @details ...
 */

/**
 * @fn void binhub_rgb_add_saturate(const binhub_rgb_t* rgb1, const binhub_rgb_t* rgb2, binhub_rgb_t* rgb)
 * @brief 分量饱和加法
 * @param rgb1 binhub_rgb_t 对象1
 * @param rgb2 binhub_rgb_t 对象2
 * @param rgb binhub_rgb_t 返回值
 * @details rgb 分量的取值范围 [0, 255], 若上溢(upflow)则截断（饱和运算），而非回绕（模运算）
 * 饱和加法，即当和超过 255 时，结果保持为最大值 255
 * @see binhub_rgb_add_modulo
 */

/**
 * @fn void binhub_rgb_add_modulo(const binhub_rgb_t* rgb1, const binhub_rgb_t* rgb2, binhub_rgb_t* rgb)
 * @brief 分量模加法
 * @param rgb1 binhub_rgb_t 对象1
 * @param rgb2 binhub_rgb_t 对象2
 * @param rgb binhub_rgb_t 返回值
 * @details rgb 分量的取值范围 [0, 255], 若上溢(upflow)则回绕（模运算），而非截断（饱和运算）
 * 模加法，当和超过 255 时，结果对 256 取模（回绕）
 * @see binhub_rgb_add_saturate
 */

/**
 * @fn void binhub_rgb_sub_saturate(const binhub_rgb_t* rgb1, const binhub_rgb_t* rgb2, binhub_rgb_t* rgb)
 * @brief 分量饱和减法
 * @param rgb1 binhub_rgb_t 对象1
 * @param rgb2 binhub_rgb_t 对象2
 * @param rgb binhub_rgb_t 返回值
 * @details rgb 分量的取值范围 [0, 255], 若下溢(underflow)则截断（饱和运算），而非回绕（模运算）
 * 饱和减法，即当差不足 0 时，结果保持为最小值 0
 * @see binhub_rgb_sub_modulo
 */

/**
 * @fn void binhub_rgb_sub_modulo(const binhub_rgb_t* rgb1, const binhub_rgb_t* rgb2, binhub_rgb_t* rgb)
 * @brief 分量模减法
 * @param rgb1 binhub_rgb_t 对象1
 * @param rgb2 binhub_rgb_t 对象2
 * @param rgb binhub_rgb_t 返回值
 * @details rgb 分量的取值范围 [0, 255], 若下溢(underflow)则回绕（模运算），而非截断（饱和运算）
 * 模减法，当差不足 0 时，结果回绕
 * @see binhub_rgb_sub_saturate
 */

/**
 * @fn void binhub_rgb_average(const binhub_rgb_t* rgb1, const binhub_rgb_t* rgb2, binhub_rgb_t* rgb)
 * @brief 平均值 - 取两个分量的平均值
 * @param rgb1 binhub_rgb_t 对象1
 * @param rgb2 binhub_rgb_t 对象2
 * @param rgb binhub_rgb_t 返回值
 */

/**
 * @fn void binhub_rgb_abs_diff(const binhub_rgb_t* rgb1, const binhub_rgb_t* rgb2, binhub_rgb_t* rgb)
 * @brief 绝对差值 - 计算两个分量差的绝对值（用于计算图像差异、边缘检测等）
 * @param rgb1 binhub_rgb_t 对象1
 * @param rgb2 binhub_rgb_t 对象2
 * @param rgb binhub_rgb_t 返回值
 */

char* binhub_rgb_to_string(const binhub_rgb_t* rgb, binhub_rgb_format_t format, char* buffer, size_t buffer_size);

void binhub_rgb_add_saturate(const binhub_rgb_t* rgb1, const binhub_rgb_t* rgb2, binhub_rgb_t* rgb);
void binhub_rgb_add_modulo(const binhub_rgb_t* rgb1, const binhub_rgb_t* rgb2, binhub_rgb_t* rgb);
void binhub_rgb_sub_saturate(const binhub_rgb_t* rgb1, const binhub_rgb_t* rgb2, binhub_rgb_t* rgb);
void binhub_rgb_sub_modulo(const binhub_rgb_t* rgb1, const binhub_rgb_t* rgb2, binhub_rgb_t* rgb);
void binhub_rgb_average(const binhub_rgb_t* rgb1, const binhub_rgb_t* rgb2, binhub_rgb_t* rgb);
void binhub_rgb_abs_diff(const binhub_rgb_t* rgb1, const binhub_rgb_t* rgb2, binhub_rgb_t* rgb);
bool binhub_hex_to_rgb(const char* hex_str, binhub_rgb_t* rgb);

/** @} */






#endif