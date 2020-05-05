#include "my_list.h"

int main(void)
{
    List *list = NULL;

    AppendNodeToList(&list, 1);
    AppendNodeToList(&list, 2);
    AppendNodeToList(&list, 3);
    AppendNodeToList(&list, 4);
    AppendNodeToList(&list, 5);
    AppendNodeToList(&list, 6);

    PrintAllNode(&list);

    DelNodeFromList(&list, 1);
    PrintAllNode(&list);

    DelNodeFromList(&list, 1);
    PrintAllNode(&list);

    DestroyList(&list);

    PrintAllNode(&list);

    return 0;
}
