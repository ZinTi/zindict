#ifndef BINHUB_STRING_H
#define BINHUB_STRING_H

/**
 * @brief Convert a hex string to decimal number.
 * @param hex_str The hex string to be converted.
 * @param p_dec The pointer to the decimal number.
 * @return 0 if success, -1 if error.
 */
int binhub_strtol(const char* hex_str, long* p_dec);

/**
 * @brief 将字符串中的所有字母转换成 uppercase
 * @param str The string to be converted.s
 */
void binhub_strupr(char* str);

/**
 * @brief 将字符串中的所有字母转换成 lowercase
 * @param str The string to be converted.s
 */
void binhub_strlwr(char* str);

/**
 * @brief 比较两个字符串是否相同，忽略大小写
 * @param str1 The first string to be compared.
 * @param str2 The second string to be compared.
 * @return 0 if the strings are equal, less than 0 if str1 is less than str2, greater than 0 if str1 is greater than str2.
 */
int binhub_strcasecmp(const char* str1, const char* str2);

/**
 * @brief 比较两个字符串是否相同，忽略大小写，最多比较前 n 个字符
 * @param str1 The first string to be compared.
 * @param str2 The second string to be compared.
 * @param n The maximum number of characters to be compared.
 * @return 0 if the strings are equal, less than 0 if str1 is less than str2, greater than 0 if str1 is greater than str2.
 */
int binhub_strncasecmp(const char* str1, const char* str2, unsigned long long n);

#endif /* BINHUB_STRING_H */
