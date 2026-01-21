/*****************************************************************
 * binhub_slls_node_t : Node SinglyLinkedList of Strings, 以字符串为节点的单链表的节点
 * binhub_slls_t     : SinglyLinkedList of Strings, 以字符串为节点的单链表
 * 
 *************************************************************/
#include "binhub_slls.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 初始化单链表
binhub_slls_t binhub_slls_init(void) {
    binhub_slls_t head = (binhub_slls_t)malloc(sizeof(binhub_slls_node_t));
    head->data = NULL;  // 头节点无数据
    head->next = NULL;
    return head;
}

// 创建新节点
binhub_slls_t binhub_slls_create_node(const char* data) {
    binhub_slls_t newbinhub_slls_node_t = (binhub_slls_t)malloc(sizeof(binhub_slls_node_t));
    if (newbinhub_slls_node_t == NULL) {
        printf("Memory allocate failed!\n");
        exit(EXIT_FAILURE); // 或者返回 NULL，根据你的设计
    }
    newbinhub_slls_node_t->data = (char*)malloc(strlen(data) + 1);
    if (newbinhub_slls_node_t->data == NULL) {
        printf("Memory allocate failed!\n");
        free(newbinhub_slls_node_t);
        exit(EXIT_FAILURE); // 或者返回 NULL
    }
    strcpy(newbinhub_slls_node_t->data, data);
    newbinhub_slls_node_t->next = NULL;
    return newbinhub_slls_node_t;
}

// 头插法新增节点
void binhub_slls_insert_head(binhub_slls_t head, const char* data) {
    binhub_slls_t newbinhub_slls_node_t = binhub_slls_create_node(data);
    newbinhub_slls_node_t->next = head->next;
    head->next = newbinhub_slls_node_t;
}

// 尾插法新增节点
void binhub_slls_insert_tail(binhub_slls_t head, const char* data) {
    binhub_slls_t newbinhub_slls_node_t = binhub_slls_create_node(data);
    binhub_slls_t p = head;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = newbinhub_slls_node_t;
}

// 查询节点位置（根据内容，返回位置从1开始）
int binhub_slls_find_node(binhub_slls_t head, const char* data) {
    binhub_slls_t p = head->next;
    int position = 1;
    while (p != NULL) {
        if (strcmp(p->data, data) == 0) {
            return position;
        }
        p = p->next;
        position++;
    }
    return -1; // 未找到返回-1
}

// 查询节点内容（根据位置）
char* binhub_slls_at(binhub_slls_t head, int position) {
    binhub_slls_t p = head->next;
    int count = 1;
    while (p != NULL && count < position) {
        p = p->next;
        count++;
    }
    if (p == NULL) {
        printf("Position is invalid!\n");
        return NULL; // 如果位置无效，返回NULL
    }
    return p->data; // 返回指定位置的节点内容
}

// 删除指定位置节点
void binhub_slls_remove_at(binhub_slls_t head, int position) {
    if (position <= 0) {
        printf("Invalid position!\n");
        return;
    }

    binhub_slls_t p = head;
    int count = 0;
    while (p->next != NULL && count < position - 1) {
        p = p->next;
        count++;
    }
    if (p->next == NULL) {
        printf("Position is invalid!\n");
        return;
    }
    binhub_slls_t temp = p->next;
    p->next = temp->next;
    free(temp->data);
    free(temp);
}

// 删除匹配内容的节点
void binhub_slls_remove_str(binhub_slls_t head, const char* data) {
    binhub_slls_t p = head;
    while (p->next != NULL && strcmp(p->next->data, data) != 0) {
        p = p->next;
    }
    if (p->next == NULL) {
        printf("No matching node was found!\n");
        return;
    }
    binhub_slls_t temp = p->next;
    p->next = temp->next;
    free(temp->data);
    free(temp);
}

// 修改节点内容（根据匹配原内容）
void binhub_slls_update_str(binhub_slls_t head, const char* old_data, const char* new_data) {
    binhub_slls_t p = head->next;
    while (p != NULL) {
        if (strcmp(p->data, old_data) == 0) {
            free(p->data);
            p->data = (char*)malloc(strlen(new_data) + 1);
            if (p->data == NULL) {
                printf("Memory allocate failed!\n");
                exit(EXIT_FAILURE); // 或者根据情况返回
            }
            strcpy(p->data, new_data);
            return;
        }
        p = p->next;
    }
    printf("No matching node was found!\n");
}

// 修改节点内容（根据指定位置）
void binhub_slls_update_at(binhub_slls_t head, int position, const char* new_data) {
    binhub_slls_t p = head->next;
    int count = 1;
    while (p != NULL && count < position) {
        p = p->next;
        count++;
    }
    if (p == NULL) {
        printf("Position is invalid!\n");
        return;
    }
    free(p->data);
    p->data = (char*)malloc(strlen(new_data) + 1);
    strcpy(p->data, new_data);
}

// 冒泡排序实现顺序排序
void binhub_slls_sort_asc(binhub_slls_t head) {
    if (head->next == NULL) return; // 空链表或单节点链表无需排序

    binhub_slls_t p, q;
    char* tempData;
    int swapped;
    do {
        swapped = 0;
        for (q = head->next; q->next != NULL; q = q->next) {
            if (strcmp(q->data, q->next->data) > 0) {
                tempData = q->data;
                q->data = q->next->data;
                q->next->data = tempData;
                swapped = 1;
            }
        }
    } while (swapped);
}

// 冒泡排序实现倒序排序
void binhub_slls_sort_desc(binhub_slls_t head) {
    if (head->next == NULL) return; // 空链表或单节点链表无需排序

    binhub_slls_t p, q;
    char* tempData;
    for (p = head->next; p != NULL; p = p->next) {
        for (q = head->next; q->next != NULL; q = q->next) {
            if (strcmp(q->data, q->next->data) < 0) {
                tempData = q->data;
                q->data = q->next->data;
                q->next->data = tempData;
            }
        }
    }
}

// 计算链表的元素个数（不包含头节点）
int binhub_slls_length(binhub_slls_t head) {
    int length = 0;
    binhub_slls_t p = head->next; // 跳过头节点
    while (p != NULL) {
        length++;
        p = p->next;
    }
    return length;
}

// 打印链表
void binhub_slls_print(binhub_slls_t head) {
    binhub_slls_t p = head->next;
    while (p != NULL) {
        printf("%s -> ", p->data);
        p = p->next;
    }
    printf("NULL\n");
}

// 释放链表内存
void binhub_slls_free(binhub_slls_t head) {
    binhub_slls_t p = head;
    while (p != NULL) {
        binhub_slls_t temp = p;
        p = p->next;
        if (temp->data) free(temp->data);
        free(temp);
    }
}
