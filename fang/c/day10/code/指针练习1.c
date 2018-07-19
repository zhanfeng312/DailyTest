/*
 *指针练习
 */
#include <stdio.h>
int main(){
    int value = 3;
    char ch = 'a';
    float fvalue = 4.7;
    void *p_value = NULL;
    p_value = &value;
    printf("value是%d\n",*(int *)p_value);
    p_value = &ch;
    printf("ch是%c\n",*(char *)p_value);
    p_value = &fvalue;
    printf("fvalue是%g\n",*(float *)p_value);

    return 0;
}
