#ifndef __MY_LIST_H__
#define __MY_LIST_H__

typedef struct MyList {
	int value;
	struct MyList *next;
} MyListNode, *MyListNodePtr;

int InitList(MyListNodePtr *list);
int AppendNewNodeToList(MyListNodePtr list, int value); //追加方式添加
int InsertNewNodeToList(MyListNodePtr list, int index, int value); //插入index前(从1开始计算)
int DelNodeFromList(MyListNodePtr list, int index); //删除index对应节点(从1开始计算)
void PrintAllNode(const MyListNodePtr list);
int GetListLen(MyListNodePtr list);
void DestroyList(MyListNodePtr *list);

#endif // __MY_LIST_H__