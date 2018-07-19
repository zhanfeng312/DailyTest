#include <stdio.h>
/*typedef struct {
    char ch;
    char c;
    double value;
} stru1;*/
typedef struct {
    int i;
    double value;
    int j;
} stru1;

int main(){
    printf("结构体大小是%d\n",sizeof(stru1));
    return 0;
}
