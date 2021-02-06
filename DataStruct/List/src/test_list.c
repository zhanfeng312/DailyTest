#include "my_list.h"
#include <stdlib.h>

int main(void)
{
    MyList *list = NULL;
    int ret = InitList(&list);
    if (ret < 0) {
        printf("InitList errno");
        exit(-1);
    }

    AppendNewNodeToList(list, 1);
    AppendNewNodeToList(list, 2);
    AppendNewNodeToList(list, 3);
    printf("Del index 2\n");
    DelNodeFromList(list, 2);
    PrintAllNode(list);
    printf("Del index 3\n");
    DelNodeFromList(list, 3);
    PrintAllNode(list);
    printf("Del index 1\n");
    DelNodeFromList(list, 1);
    PrintAllNode(list);
    printf("Del index 4\n");
    DelNodeFromList(list, 4);
    PrintAllNode(list);
    printf("Del index 1\n");
    DelNodeFromList(list, 1);
    PrintAllNode(list);

    int len = GetListLen(list);
    printf("list len is %d\n", len);

    DestroyList(&list);

    printf("list is %p\n", list);

    return 0;
}
