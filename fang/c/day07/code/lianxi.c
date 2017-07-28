#include <stdio.h>
int main(){
    char c = 0;
    scanf("%c",&c);
    switch (c){
        case 'a':
            printf("对应的数为10\n");
            break;
        case 'b':
            printf("对应的数为11\n");
            break;
        case 'c':
            printf("对应的数为12\n");
            break;
        case 'd':
            printf("对应的数为13\n");
            break;
        case 'e':
            printf("对应的数为14\n");
            break;
        case 'f':
            printf("对应的数为15\n");
            break;
        default:
            printf("输入的字符有误！\n");
            break;

    }

    return 0;
}
