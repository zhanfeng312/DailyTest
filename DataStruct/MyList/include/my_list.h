#ifndef __MY_LIST_H__
#define __MY_LIST_H__

#include <stdio.h>

typedef struct MyList {
	int value;
	struct MyList *next;
} MyList;

/* 初始化一个空链表 */
int InitList(MyList **list);
int AppendNewNodeToList(MyList *list, int value);
//void InsertNewNodeToList(MyList *head, int index);
void DelNodeFromList(MyList *list, int index);
void PrintAllNode(const MyList *list);
int GetListLen(const MyList *list);
void DestroyList(MyList **list);

#endif // __MY_LIST_H__