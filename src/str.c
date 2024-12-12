#include "str.h"

void StrToUppercase(char *str) {
    while (*str) {
        if (*str >= 'a' && *str <= 'z') {
            *str = *str - 'a' + 'A';
        }
        str++;
    }
}

void StrToLowercase(char *str) {
    while (*str) {
        if (*str >= 'A' && *str <= 'Z') {
            *str = *str - 'A' + 'a';
        }
        str++;
    }
}

int StrCmpIgnoreCase(const char *str1, const char *str2) {
    while (*str1 && *str2) {
        char c1 = (*str1 >= 'A' && *str1 <= 'Z') ? (*str1 - 'A' + 'a') : *str1;
        char c2 = (*str2 >= 'A' && *str2 <= 'Z') ? (*str2 - 'A' + 'a') : *str2;
        if (c1 != c2) {
            return c1 - c2; // 返回字符差值，类似于strcmp
        }
        str1++;
        str2++;
    }
    return *str1 - *str2; // 考虑到字符串长度不同的情况
}

int StrNCmpIgnoreCase(const char *str1, const char *str2, unsigned long long n) {
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