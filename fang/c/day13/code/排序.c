/*
 * 排序练习
 */
#include <stdio.h>
#include<stdlib.h>
int compare(const void *p_value, const void *p_value1) {  //可以比较任何两个数
    const int *p_int = (const int*)p_value;             //先类型转换
    const int *p_int1 = (const int*)p_value1;
    if(*p_int < *p_int1) {
        return -1;
    }
    else if(*p_int > *p_int1){
        return 1;
    }
    else {
        return 0;
    }
}
int compare1(const void *p_value, const void *p_value1) {
    return 0 - compare(p_value, p_value1);
}
int main(){
    int values[] = {8, 4, 2, 6};
    int loop = 0;
    qsort(values, 4, sizeof(int),compare1);
    for(loop = 0;loop <= 3;loop++) {
        printf("%d ", values[loop]);
    }
    printf("\n");
    return 0;
}

