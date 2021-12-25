#include "my_list.h"
#include <stdio.h>
#include <stdlib.h>

static MyListNodePtr g_listHead = NULL;

int main(void)
{
    InitList(&g_listHead);

    AppendNewNodeToList(g_listHead, 1);
    AppendNewNodeToList(g_listHead, 2);
    AppendNewNodeToList(g_listHead, 3);

    PrintAllNode(g_listHead);

    InsertNewNodeToList(g_listHead, 1, 4);
    PrintAllNode(g_listHead);

    InsertNewNodeToList(g_listHead, 2, 5);
    PrintAllNode(g_listHead);
    
    DelNodeFromList(g_listHead, 1);
    PrintAllNode(g_listHead);

    DestroyList(&g_listHead);

    PrintAllNode(g_listHead);
    return 0;
}
