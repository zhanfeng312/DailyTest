/*
 * 堆练习
 */
#include <stdio.h>
#include <stdlib.h>
int main(){
    int *p_value = (int *)calloc(4, sizeof(int));//保证四个整数都为0
    int *p_value1 = NULL;
    if(p_value) {
         p_value1 = realloc(p_value, 6 * sizeof(int));
         if(p_value1) {
             p_value = p_value1;
         }
         free(p_value);
         p_value = NULL;
    }

    return 0;
}
