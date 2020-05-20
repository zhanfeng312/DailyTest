#include "my_list.h"
#include <stdlib.h>

void AppendNodeToList(List **list, int value)
{
    List *temp = NULL;
    List *newNode = NULL;

    if (*list == NULL) { //表头为空，创建表头
        *list = (List*)calloc(1, sizeof(List));
        if (*list == NULL) {
            printf("calloc failed\n");
            return;
        }
        (*list)->value = value;
        (*list)->next = NULL;
    } else {
        newNode = (List*)calloc(1, sizeof(List));
        if (newNode == NULL) {
            printf("calloc failed\n");
            return;
        }
        newNode->value = value;
        newNode->next = NULL;

        temp = *list;
        while (temp != NULL) {
            if (temp->next == NULL) { //最后一个节点
                temp->next = newNode;
                break;
            }
            temp = temp->next;
        }
    }
    printf("append %d success!\n", value);
}

void DelNodeFromList(List **list, int index)
{
    List *temp = NULL;
    List *prev = NULL;
    int num = GetListLen(list);
    int indexBackup = index;

    if (*list == NULL || index < 0 || index > num) {
        printf("argument is illegal!\n");
        return ;
    }

    temp = *list;

    while (temp != NULL) {
        index--;
        if (index == 0) {
            if (temp->next == NULL) {
                if (prev == NULL) {   //有且只有一个
                    *list = NULL;
                } else {              //如果最后一个
                    prev->next = NULL;
                }
            } else if (prev == NULL) { //第一个
                *list = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp);
            temp = NULL;
            break;
        }
        prev = temp;
        temp = temp->next;
    }

    printf("Del index %d success!\n", indexBackup);
}

void PrintAllNode(List **list)
{
    if (*list == NULL) {
        printf("The list is empty!\n");
        return;
    }

    List *temp = *list;

    printf("All node value is:");
    while (temp != NULL) {
        printf("%d ", temp->value);
        temp = temp->next;
    }
    printf("\n");
}

int GetListLen(List **list)
{
    List *temp = *list;
    int count = 0;

    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    return count;
}

void DestroyList(List **list)
{
    List *temp = *list;
    List *del = NULL;

    while(temp != NULL) {
        del = temp;
        temp = temp->next;
        free(del);
        del = NULL;
    }

    *list = NULL;
}

