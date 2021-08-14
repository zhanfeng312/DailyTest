#include "my_list.h"
#include <stdio.h>
#include <stdlib.h>

#define CHECK_LIST_WITHOUT_RETURN(list)  do { \
    if ((list) == NULL) { \
        printf("The list is null\n"); \
        return; \
    } \
} while (0);

#define CHECK_LIST_WITH_RETURN(list, ret)  do { \
    if ((list) == NULL) { \
        printf("The list is null\n"); \
        return (ret); \
    } \
} while (0);

int InitList(MyListNodePtr *list)
{
    CHECK_LIST_WITH_RETURN(list, -1);

    *list = (MyListNodePtr)calloc(1, sizeof(MyListNode));
    if (*list == NULL) {
        printf("calloc failed\n");
        return -1;
    }
    (*list)->next = NULL;
}

int AppendNewNodeToList(MyListNodePtr list, int value)
{
    CHECK_LIST_WITH_RETURN(list, -1);

    MyListNodePtr newNode = (MyListNodePtr)calloc(1, sizeof(MyListNode));
    if (newNode == NULL) {
        printf("calloc failed\n");
        return -1;
    }
    newNode->next = NULL;
    newNode->value = value;

    MyListNodePtr node = list;
    //找到链表最后一个节点
    while (node->next != NULL) {
        node = node->next;
    }
    node->next = newNode;
    printf("append %d success!\n", value);
    return 0;
}

/* 插入index前(从1开始计算) */
int InsertNewNodeToList(MyListNodePtr list, int index, int value)
{
    if ((index < 0) || (index > GetListLen(list))) {
        printf("Invalid index.\n");
        return -1;
    }
    //找到index对应的节点
    MyListNodePtr node = list;
    MyListNodePtr newNode;
    int curIndex = 1;
    while (node->next != NULL) {
        if (curIndex == index) {
            InitList(&newNode);
            newNode->next = node->next;
            newNode->value = value;
            node->next = newNode;
        }
        curIndex++;
        node = node->next;
    }
    printf("Insert new node index(%d), value(%d) success.\n", index, value);
}

/* 删除index的节点 */
int DelNodeFromList(MyListNodePtr list, int index)
{
    if ((index < 0) || (index > GetListLen(list))) {
        printf("Invalid index.\n");
        return -1;
    }
    //找到index对应的节点
    MyListNodePtr node = list;
    MyListNodePtr delNode;
    int curIndex = 1;
    while (node->next != NULL) {
        if (curIndex == index) {
            delNode = node->next;
            node->next = delNode->next;
            free(delNode);
        }
        curIndex++;
        node = node->next;
    }
    printf("Del new node index(%d) success.\n", index);
}

void PrintAllNode(const MyListNodePtr list)
{
    CHECK_LIST_WITHOUT_RETURN(list);

    MyListNodePtr curNode = list;
    printf("All node value is:");
    while (curNode->next != NULL) {
        printf("%d ", curNode->next->value);
        curNode = curNode->next;
    }
    printf("\n");
}

int GetListLen(const MyListNodePtr list)
{
    CHECK_LIST_WITH_RETURN(list, -1);

    MyListNodePtr curNode = list;
    int count = 0;
    while (curNode->next != NULL) {
        count++;
        curNode = curNode->next;
    }
    return count;
}

void DestroyList(MyListNodePtr *list)
{
    CHECK_LIST_WITHOUT_RETURN(list);

    MyListNodePtr curNode = *list;
    MyListNodePtr delNode = NULL;
    while(curNode->next != NULL) {
        delNode = curNode->next;
        curNode->next = delNode->next;
        free(delNode);
    }
    //销毁头结点
    free(*list);
    *list = NULL;
}