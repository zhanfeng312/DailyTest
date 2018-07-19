/*
 * malloc练习
 * 栈的管理,申请内存后,一定要销毁它
 */
#include <stdio.h>
#include <stdlib.h>
int main(){
    
    int *p_value = (int *) malloc(1 * sizeof(int));
    if(p_value){
         printf("value是%d\n", *p_value);
         free(p_value);
         p_value = NULL;
    }
       return 0;
}
