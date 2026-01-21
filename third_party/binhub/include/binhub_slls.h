/*****************************************************************
 * binhub_slls_node_t : Node SinglyLinkedList of String, 以字符串为节点的单链表的节点
 * binhub_slls_t     : SinglyLinkedList of String, 以字符串为节点的单链表
 * 
 * 
 *************************************************************/
#ifndef BINHUB_SLLS_H
#define BINHUB_SLLS_H

// 定义链表节点结构体
typedef struct binhub_slls_node_t {
    char* data;
    struct binhub_slls_node_t* next;
} binhub_slls_node_t, *binhub_slls_t;

/**
 * @brief 初始化单链表
 * @return
 */
binhub_slls_t binhub_slls_init(void);

/**
 * @brief 创建新节点
 * @param data 节点数据
 * @return 节点指针
 */
binhub_slls_t binhub_slls_create_node(const char* data);

/**
 * @brief 头插法新增节点
 * @param head
 * @param data
 */
void binhub_slls_insert_head(binhub_slls_t head, const char* data);

/**
 * @brief 尾插法新增节点
 * @param head
 * @param data
 */
void binhub_slls_insert_tail(binhub_slls_t head, const char* data);

/**
 * @brief 查询节点位置（根据内容，返回位置从1开始）
 * @param head
 * @param data
 * @return
 */
int binhub_slls_find_node(binhub_slls_t head, const char* data);

/**
 * @brief 按索引获取节点内容
 * @param head
 * @param position
 * @return
 */
char* binhub_slls_at(binhub_slls_t head, int position);

/**
 * @brief 删除指定位置的节点
 * @param head
 * @param position
 */
void binhub_slls_remove_at(binhub_slls_t head, int position);

/**
 * @brief 删除匹配内容的节点
 * @param head
 * @param data
 */
void binhub_slls_remove_str(binhub_slls_t head, const char* data);

/**
 * @brief 修改节点内容（依据匹配）
 * @param head
 * @param old_data
 * @param new_data
 */
void binhub_slls_update_str(binhub_slls_t head, const char* old_data, const char* new_data);

/**
 * @brief 修改节点内容（依据位置）
 * @param head
 * @param position
 * @param new_data
 */
void binhub_slls_update_at(binhub_slls_t head, int position, const char* new_data);

/**
 * @brief 顺序排序（冒泡排序实现）
 * @param head 链表头节点
 */
void binhub_slls_sort_asc(binhub_slls_t head);

/**
 * @brief 倒序排序（冒泡排序实现）
 * @param head 链表头节点
 */
void binhub_slls_sort_desc(binhub_slls_t head);

/**
 * @brief 计算链表的元素个数（不包含头节点）
 * @param head
 * @return
 */
int binhub_slls_length(binhub_slls_t head);

/**
 * @brief 打印链表内容
 * @param head 链表头节点
 */
void binhub_slls_print(binhub_slls_t head);

/**
 * @brief 释放链表内存
 * @param head
 */
void binhub_slls_free(binhub_slls_t head);

#endif
