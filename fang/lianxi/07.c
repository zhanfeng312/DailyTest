#include <stdio.h>
int main(void){
    int select = 0;
    int b = 3;
    scanf("%d", &select);
    switch (select){
        case 1:case 2:
            printf("%d\n", b);
        default:
            printf("default\n");
    }
    printf("%d\n", sizeof (int));
    return 0;
}
