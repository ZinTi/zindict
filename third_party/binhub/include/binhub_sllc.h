/*****************************************************************
 * binhub_sllc_node_t : Node SinglyLinkedList of Char, 以字符为节点的单链表的节点
 * binhub_sllc     : SinglyLinkedList of Char, 以字符为节点的单链表
 * 
 * 
 *************************************************************/
#ifndef BINHUB_SLLC_H
#define BINHUB_SLLC_H

// 定义链表节点结构体
typedef struct binhub_sllc_node_t {
    char data;
    struct binhub_sllc_node_t* next;
} binhub_sllc_node_t, *binhub_sllc_t;

/**
 * @brief 初始化链表
 */
binhub_sllc_t binhub_sllc_init(void);

/**
 * @brief 头插法新增节点
 * @param head 链表头指针
 * @param data 新增节点的数据
 */
void binhub_sllc_insert_head(binhub_sllc_t head, char data);

/**
 * @brief 尾插法新增节点
 * @param head 链表头指针
 * @param data 新增节点的数据
 */
void binhub_sllc_insert_tail(binhub_sllc_t head, char data);

/**
 * @brief 查询第一次出现某字符的节点位置
 * @param head 链表头指针
 * @param data 目标字符数据
 * @return 第一个出现的节点位置，-1表示未找到
 */
int binhub_sllc_first_index(binhub_sllc_t head, char data);

/**
 * @brief 查询最后一次出现某字符的节点位置
 * @param head 链表头指针
 * @param data 目标字符数据
 * @return 最后一次出现的节点位置，-1表示未找到
 */
int binhub_sllc_last_index(binhub_sllc_t head, char data);

/**
 * @brief 获取指定位置的元素（字符内容）
 * @param head 链表头指针
 * @param index 指定位置
 * @return 字符内容
 */
char binhub_sllc_at(binhub_sllc_t head, int index);

/**
 * @brief 删除指定位置的节点
 * @param head 链表头指针
 * @param index 指定位置
 */
void binhub_sllc_remove_at(binhub_sllc_t head, int index);

/**
 * @brief 修改指定位置的节点内容
 * @param head 链表头指针
 * @param index 指定位置
 * @param new_data 新数据
 */
void binhub_sllc_update_at(binhub_sllc_t head, int index, char new_data);

/**
 * @brief 计算链表长度
 * @param head 链表头指针
 * @return 链表长度
 */
int binhub_sllc_length(binhub_sllc_t head);

/**
 * @brief 打印链表内容
 * @param head 链表头指针
 */
void binhub_sllc_print(binhub_sllc_t head);

/**
 * @brief 顺序排序
 * @param head 链表头指针
 */
void binhub_sllc_sort(binhub_sllc_t head);

/**
 * @brief 倒序排序
 * @param head 链表头指针
 */
void binhub_sllc_sort_reverse(binhub_sllc_t head);

/**
 * @brief 在链表尾部追加字符串作为一串节点
 * @param head 链表头指针
 * @param str 追加的字符串
 */
void binhub_sllc_append_str(binhub_sllc_t head, const char* str);

/**
 * @brief 复制链表（深复制）
 * @param head 链表头指针
 * @return 新链表
 */
binhub_sllc_t binhub_sllc_copy(binhub_sllc_t head);

/**
 * @brief 将链表内容拼接成字符串
 * @param head 链表头指针
 * @return 字符串
 */
char* binhub_sllc_to_str(binhub_sllc_t head);

/**
 * @brief 释放链表内存
 * @param head 链表头指针
 */
void binhub_sllc_free(binhub_sllc_t head);

#endif
