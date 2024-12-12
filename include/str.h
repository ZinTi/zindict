#ifndef INC_STR_H
#define INC_STR_H

/*--------------------（一）声明函数原型-------------------------*/
/**
 * @brief 将字符串中的所有英文字母转换成大写
 * @param str 字符串
 */
void StrToUppercase(char *str);

/**
 * @brief 将字符串中的所有英文字母转换成小写
 * @param str 字符串
 */
void StrToLowercase(char *str);

/**
 * @brief 比较两个字符串是否相同，忽略大小写
 * @param str1 第一个字符串
 * @param str2 第二个字符串
 * @return 两个字符串的相差字母数，如果为0则表示相同
 */
int StrCmpIgnoreCase(const char *str1, const char *str2);

/**
 * @brief 比较两个字符串的前n个字符是否相同，忽略大小写
 * @param str1 第一个字符串
 * @param str2 第二个字符串
 * @param n 比较的字符数
 * @return 如果为0则表示两个字符串相同
 */
int StrNCmpIgnoreCase(const char *str1, const char *str2, unsigned long long n);


#endif // INC_STR_H