#ifndef __MY_LIST_H__
#define __MY_LIST_H__

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct List {
	int value;
	struct List *next;
} List;

void AppendNodeToList(List **list, int value);
void DelNodeFromList(List **list, int index);
void PrintAllNode(List **list);
int GetListLen(List **list);
void DestroyList(List **list);

#ifdef __cplusplus
}
#endif

#endif // __MY_LIST_H__