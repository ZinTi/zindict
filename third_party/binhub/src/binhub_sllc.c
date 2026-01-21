/*****************************************************************
 * binhub_sllc_node_t : Node SinglyLinkedList of Char, 以字符为节点的单链表的节点
 * binhub_sllc_t     : SinglyLinkedList of Char, 以字符为节点的单链表
 * 
 *************************************************************/
#include "binhub_sllc.h"
#include <stdio.h>
#include <stdlib.h>

// 初始化链表
binhub_sllc_t binhub_sllc_init(void) {
    binhub_sllc_t head = (binhub_sllc_t)malloc(sizeof(binhub_sllc_node_t));
    head->next = NULL;
    return head;
}

// 头插法新增节点
void binhub_sllc_insert_head(binhub_sllc_t head, const char data) {
    binhub_sllc_t new_node = (binhub_sllc_t)malloc(sizeof(binhub_sllc_node_t));
    new_node->data = data;
    new_node->next = head->next;
    head->next = new_node;
}

// 尾插法新增节点
void binhub_sllc_insert_tail(binhub_sllc_t head, const char data) {
    binhub_sllc_t new_node = (binhub_sllc_t)malloc(sizeof(binhub_sllc_node_t));
    new_node->data = data;
    new_node->next = NULL;

    binhub_sllc_t temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_node;
}

// 查询第一次出现某字符的节点位置
int binhub_sllc_first_index(binhub_sllc_t head, const char data) {
    int pos = 0;
    binhub_sllc_t temp = head->next;
    while (temp != NULL) {
        if (temp->data == data) {
            return pos;
        }
        pos++;
        temp = temp->next;
    }
    return -1;
}

// 查询最后一次出现某字符的节点位置
int binhub_sllc_last_index(binhub_sllc_t head, const char data) {
    int pos = 0, lastPos = -1;
    binhub_sllc_t temp = head->next;
    while (temp != NULL) {
        if (temp->data == data) {
            lastPos = pos;
        }
        pos++;
        temp = temp->next;
    }
    return lastPos;
}

// 查询指定位置的字符内容
char binhub_sllc_at(binhub_sllc_t head, const int index) {
    int pos = 0;
    binhub_sllc_t temp = head->next;
    while (temp != NULL) {
        if (pos == index) {
            return temp->data;
        }
        pos++;
        temp = temp->next;
    }
    return '\0'; // 返回空字符表示未找到
}

// 删除指定位置的节点
void binhub_sllc_remove_at(binhub_sllc_t head, const int index) {
    int pos = 0;
    binhub_sllc_t temp = head, prev = NULL;

    while (temp->next != NULL && pos < index) {
        prev = temp;
        temp = temp->next;
        pos++;
    }

    if (temp->next == NULL || pos != index) return;

    prev->next = temp->next;
    free(temp);
}

// 修改指定位置的节点内容
void binhub_sllc_update_at(binhub_sllc_t head, const int index, const char new_data) {
    int pos = 0;
    binhub_sllc_t temp = head->next;

    while (temp != NULL) {
        if (pos == index) {
            temp->data = new_data;
            return;
        }
        pos++;
        temp = temp->next;
    }
}

// 计算链表长度
int binhub_sllc_length(binhub_sllc_t head) {
    int len = 0;
    binhub_sllc_t temp = head->next;
    while (temp != NULL) {
        len++;
        temp = temp->next;
    }
    return len;
}

// 打印链表内容
void binhub_sllc_print(binhub_sllc_t head) {
    binhub_sllc_t temp = head->next;
    while (temp != NULL) {
        printf("%c -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// 顺序排序
void binhub_sllc_sort(binhub_sllc_t head) {
    if (head->next == NULL || head->next->next == NULL) return;

    binhub_sllc_t i, j;
    char temp;
    for (i = head->next; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->data > j->data) {
                temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}

// 倒序排序
void binhub_sllc_sort_reverse(binhub_sllc_t head) {
    if (head->next == NULL || head->next->next == NULL) return;

    binhub_sllc_t i, j;
    char temp;
    for (i = head->next; i != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->data < j->data) {
                temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}

// 在链表尾部追加字符串作为一串节点
void binhub_sllc_append_str(binhub_sllc_t head, const char* str) {
    binhub_sllc_t temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    while (*str) {
        binhub_sllc_t new_node = (binhub_sllc_t)malloc(sizeof(binhub_sllc_node_t));
        new_node->data = *str;
        new_node->next = NULL;
        temp->next = new_node;
        temp = new_node;
        str++;
    }
}

// 复制链表（深复制）
binhub_sllc_t binhub_sllc_copy(binhub_sllc_t head) {
    if (head == NULL) return NULL;

    binhub_sllc_t newHead = (binhub_sllc_t)malloc(sizeof(binhub_sllc_node_t));
    newHead->next = NULL;
    binhub_sllc_t newTemp = newHead;

    binhub_sllc_t temp = head->next;
    while (temp != NULL) {
        binhub_sllc_t new_node = (binhub_sllc_t)malloc(sizeof(binhub_sllc_node_t));
        new_node->data = temp->data;
        new_node->next = NULL;
        newTemp->next = new_node;
        newTemp = new_node;
        temp = temp->next;
    }
    return newHead;
}

// 将链表内容拼接成字符串
char* binhub_sllc_to_str(binhub_sllc_t head) {
    int len = 0;
    binhub_sllc_t temp = head->next;
    while (temp != NULL) {
        len++;
        temp = temp->next;
    }

    char* str = (char*)malloc(len + 1); // 为字符串分配内存
    str[len] = '\0'; // 确保字符串结尾为 '\0'

    temp = head->next;
    for (int i = 0; i < len; i++) {
        str[i] = temp->data;
        temp = temp->next;
    }

    return str;
}

// 释放链表内存
void binhub_sllc_free(binhub_sllc_t head) {
    binhub_sllc_t temp = head;
    while (temp != NULL) {
        binhub_sllc_t next = temp->next;
        free(temp);
        temp = next;
    }
}