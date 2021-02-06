#include "my_list.h"
#include <stdlib.h>
#include <errno.h>

/* 初始化一个空链表 */
int InitList(MyList **list)
{
    *list = (MyList *)malloc(sizeof(MyList));
    if (*list == NULL) {
        printf("malloc error, errno is %d\n", errno);
        return -1;
    }
    (*list)->next = NULL;
    return 0;
}

int AppendNewNodeToList(MyList *list, int value)
{
    MyList *newNode = (MyList *)calloc(1, sizeof(MyList));
    if (newNode == NULL) {
        printf("calloc failed\n");
        return -1;
    }
    newNode->next = NULL;
    newNode->value = value;

    //找到链表最后一个节点
    MyList *node = list;
    while (node->next != NULL) {
        node = node->next;
    }
    //退出循环, node指向最后一个节点
    node->next = newNode;
    printf("append %d success!\n", value);
    return 0;
}

#if 0
void InsertNewNodeToList(MyList *list, int index)
{
    if (list == NULL || index < 0 || index > GetListLen(list)) {
        printf("argument is illegal!\n");
        return ;
    }

    MyList *temp = list;
    while (temp->next != NULL) {
        index--;
        if (index == 0) {
            delNode = temp->next;
            temp->next = delNode->next;
            free(delNode);
            delNode = NULL;
            break;
        }
        temp = temp->next;
    }
    printf("Del index %d success!\n", indexBackup);
}
#endif

void DelNodeFromList(MyList *list, int index)
{
    MyList *temp = list;
    MyList *delNode = NULL;
    int backupIndex = index;

    if (list == NULL || index < 0 || index > GetListLen(list)) {
        printf("argument is illegal!\n");
        return ;
    }

    while (temp->next != NULL) {
        index--;
        if (index == 0) {
            delNode = temp->next;
            temp->next = delNode->next;
            free(delNode);
            delNode = NULL;
            break;
        }
        temp = temp->next;
    }
    printf("Del index(%d) success!\n", backupIndex);
}

void PrintAllNode(const MyList *list)
{
    if (list == NULL) {
        printf("The list is empty!\n");
        return;
    }

    const MyList *node = list;
    printf("All node value is:");
    while (node->next != NULL) {
        printf("%d ", node->next->value);
        node = node->next;
    }
    printf("\n");
}

int GetListLen(const MyList *list)
{
    const MyList *node = list;
    int count = 0;

    while (node->next != NULL) {
        count++;
        node = node->next;
    }
    return count;
}

void DestroyList(MyList **list)
{
    MyList *node = *list;
    MyList *delNode = NULL;

    while(node->next != NULL) {
        delNode = node->next;
        node->next = delNode->next;
        free(delNode);
        delNode = NULL;
    }

    //删除头结点
    free(*list);
    *list = NULL;
}