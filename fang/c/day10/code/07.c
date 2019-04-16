#include <stdio.h>
int main(){
    int value = 0;
    int *p_value = NULL;  //NULL表示空地址

    p_value = &value;
    printf("大小是%d %d\n",sizeof(p_value),sizeof(int *));

    return 0;
}
