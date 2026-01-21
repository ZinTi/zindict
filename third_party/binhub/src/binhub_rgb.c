#include "binhub_rgb.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>

struct binhub_rgb_t {
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

// 静态内联饱和加
static inline uint8_t sat_add(const uint8_t a, const uint8_t b) {
    return (a > 255 - b) ? 255 : a + b;
    // return (uint8_t)((rgb1->r + rgb2->r) | -(rgb1->r + rgb2->r < rgb1->r));
}

binhub_rgb_t* binhub_rgb_new(const uint8_t red, const uint8_t green, const uint8_t blue){
    binhub_rgb_t* new_rgb = (binhub_rgb_t*)malloc(sizeof(binhub_rgb_t));
    if(new_rgb){
        new_rgb->r = red;
        new_rgb->g = green;
        new_rgb->b = blue;
    }
    return new_rgb;
}

void binhub_rgb_delete(binhub_rgb_t* rgb){
    if(rgb) free(rgb);
}

uint8_t binhub_rgb_get_red(const binhub_rgb_t* rgb){
    return rgb->r;
}

uint8_t binhub_rgb_get_green(const binhub_rgb_t* rgb){
    return rgb->g;
}

uint8_t binhub_rgb_get_blue(const binhub_rgb_t* rgb){
    return rgb->b;
}

void binhub_rgb_set_red(binhub_rgb_t* rgb, const uint8_t red){
    rgb->r = red;
}

void binhub_rgb_set_green(binhub_rgb_t* rgb, const uint8_t green){
    rgb->g = green;
}

void binhub_rgb_set_blue(binhub_rgb_t* rgb, const uint8_t blue){
    rgb->b = blue;
}

char* binhub_rgb_to_string(const binhub_rgb_t* rgb, const binhub_rgb_format_t format, char* buffer, const size_t buffer_size) {
    if (rgb == NULL || buffer == NULL || buffer_size == 0) {
        return NULL;
    }

    switch (format) {
        case RGB_FORMAT_CSV:
            if (snprintf(buffer, buffer_size, "%u,%u,%u", rgb->r, rgb->g, rgb->b) >= buffer_size) { return NULL; }
            break;
        case RGB_FORMAT_HEX:
            if (snprintf(buffer, buffer_size, "#%02X%02X%02X", rgb->r, rgb->g, rgb->b) >= buffer_size) { return NULL; }
            break;
        case RGB_FORMAT_CSS:
            if (snprintf(buffer, buffer_size, "rgb(%u, %u, %u)", rgb->r, rgb->g, rgb->b) >= buffer_size) { return NULL; }
            break;
        default:
            if (snprintf(buffer, buffer_size, "%u,%u,%u", rgb->r, rgb->g, rgb->b) >= buffer_size) { return NULL; }
    }
    return buffer; // 链式调用
}

void binhub_rgb_add_saturate(const binhub_rgb_t* rgb1, const binhub_rgb_t* rgb2, binhub_rgb_t* rgb){
    if (rgb1 == NULL || rgb2 == NULL || rgb == NULL) {
        return;
    }

    rgb->r = sat_add(rgb1->r, rgb2->r);
    rgb->g = sat_add(rgb1->g, rgb2->g);
    rgb->b = sat_add(rgb1->b, rgb2->b);
}

void binhub_rgb_add_modulo(const binhub_rgb_t* rgb1, const binhub_rgb_t* rgb2, binhub_rgb_t* rgb){
    if (rgb1 == NULL || rgb2 == NULL || rgb == NULL) {
        return;
    }

    rgb->r = rgb1->r + rgb2->r;
    rgb->g = rgb1->g + rgb2->g;
    rgb->b = rgb1->b + rgb2->b;
}

void binhub_rgb_sub_saturate(const binhub_rgb_t* rgb1, const binhub_rgb_t* rgb2, binhub_rgb_t* rgb){
    if (rgb1 == NULL || rgb2 == NULL || rgb == NULL) {
        return;
    }

    rgb->r = (uint8_t)((int)rgb1->r - rgb2->r < 0 ? 0 : rgb1->r - rgb2->r);
    rgb->g = (uint8_t)((int)rgb1->g - rgb2->g < 0 ? 0 : rgb1->g - rgb2->g);
    rgb->b = (uint8_t)((int)rgb1->b - rgb2->b < 0 ? 0 : rgb1->b - rgb2->b);
}

void binhub_rgb_sub_modulo(const binhub_rgb_t* rgb1, const binhub_rgb_t* rgb2, binhub_rgb_t* rgb){
    if (rgb1 == NULL || rgb2 == NULL || rgb == NULL) {
        return;
    }

    rgb->r = rgb1->r - rgb2->r;
    rgb->g = rgb1->g - rgb2->g;
    rgb->b = rgb1->b - rgb2->b;
}

void binhub_rgb_average(const binhub_rgb_t* rgb1, const binhub_rgb_t* rgb2, binhub_rgb_t* rgb){
    if (rgb1 == NULL || rgb2 == NULL || rgb == NULL) {
        return;
    }

    rgb->r = (uint8_t)(((int)rgb1->r + rgb2->r + 1) / 2);
    rgb->g = (uint8_t)(((int)rgb1->g + rgb2->g + 1) / 2);
    rgb->b = (uint8_t)(((int)rgb1->b + rgb2->b + 1) / 2);
}

void binhub_rgb_abs_diff(const binhub_rgb_t* rgb1, const binhub_rgb_t* rgb2, binhub_rgb_t* rgb){
    if (rgb1 == NULL || rgb2 == NULL || rgb == NULL) {
        return;
    }

    rgb->r = abs(rgb1->r - rgb2->r);
    rgb->g = abs(rgb1->g - rgb2->g);
    rgb->b = abs(rgb1->b - rgb2->b);
}

bool binhub_hex_to_rgb(const char* hex_str, binhub_rgb_t* rgb) {
    if (!hex_str || !rgb) return false;

    size_t len = strlen(hex_str);
    char normalized[8] = {0};

    // 处理简写格式 #RGB
    if (len == 4 && hex_str[0] == '#') {
        snprintf(normalized, sizeof(normalized), "#%c%c%c%c%c%c",
                 hex_str[1], hex_str[1],
                 hex_str[2], hex_str[2],
                 hex_str[3], hex_str[3]);
        hex_str = normalized;
        len = 7;
    }
    // 处理无#前缀格式
    else if (len == 6 && hex_str[0] != '#') {
        snprintf(normalized, sizeof(normalized), "#%s", hex_str);
        hex_str = normalized;
        len = 7;
    }

    // 验证最终格式
    if (len != 7 || hex_str[0] != '#') {
        return false;
    }

    // 转换十六进制值
    uint32_t color = 0;
    for (int i = 1; i < 7; i++) {
        char c = tolower(hex_str[i]);
        color <<= 4;

        if (c >= '0' && c <= '9') color |= c - '0';
        else if (c >= 'a' && c <= 'f') color |= 10 + (c - 'a');
        else return false;
    }

    // 提取RGB分量
    rgb->r = (color >> 16) & 0xFF;
    rgb->g = (color >> 8) & 0xFF;
    rgb->b = color & 0xFF;

    return true;
}

/*
bool binhub_hex_to_rgb(const char* hex_str, binhub_rgb_t* rgb) {
    uint8_t r, g, b;
    const int count =  sscanf(hex_str, "%2x%2x%2x", &r, &g, &b);
    binhub_rgb_set_red(rgb, &r);
    binhub_rgb_set_green(rgb, &g);
    binhub_rgb_set_blue(rgb, &b);
    return count == 3;
}*/