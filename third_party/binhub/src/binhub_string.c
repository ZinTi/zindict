#include "binhub_string.h"
#include <stdlib.h>
#include <stdio.h>

// Convert a hex string to decimal number.
int binhub_strtol(const char* hex_str, long* p_dec){
    char* endptr;
    strtol(hex_str, &endptr, 16);
    if (*endptr != '\0') {
        puts("Error: Invalid hexadecimal number.");
        return -1;
    }
    *p_dec = strtol(hex_str, NULL, 16);
    return 0;
}

// 将字符串中的所有字母转换成大写
void binhub_strupr(char* str) {
    while (*str) {
        if (*str >= 'a' && *str <= 'z') {
            *str = *str - 'a' + 'A';
        }
        str++;
    }
}

// 将字符串中的所有字母转换成小写
void binhub_strlwr(char* str) {
    while (*str) {
        if (*str >= 'A' && *str <= 'Z') {
            *str = *str - 'A' + 'a';
        }
        str++;
    }
}

// 比较两个字符串是否相同，忽略大小写
int binhub_strcasecmp(const char* str1, const char* str2) {
    while (*str1 && *str2) {
        char c1 = (*str1 >= 'A' && *str1 <= 'Z') ? (*str1 - 'A' + 'a') : *str1;
        char c2 = (*str2 >= 'A' && *str2 <= 'Z') ? (*str2 - 'A' + 'a') : *str2;
        if (c1 != c2) {
            return c1 - c2; // 返回字符差值，类似于strcmp
        }
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

// 比较两个字符串的前n个字符是否相同，忽略大小写
int binhub_strncasecmp(const char* str1, const char* str2, unsigned long long n) {
    while (n && *str1 && *str2) {
        char c1 = (*str1 >= 'A' && *str1 <= 'Z') ? (*str1 - 'A' + 'a') : *str1;
        char c2 = (*str2 >= 'A' && *str2 <= 'Z') ? (*str2 - 'A' + 'a') : *str2;
        if (c1 != c2) {
            return c1 - c2; // 返回字符差值
        }
        str1++;
        str2++;
        n--;
    }

    // 如果 n 为 0 或两个字符串在前 n 个字符都相等，则返回 0
    if (n == 0) {
        return 0;
    }

    // 处理字符串长度不同的情况
    return (*str1) ? 1 : ((*str2) ? -1 : 0);
}
