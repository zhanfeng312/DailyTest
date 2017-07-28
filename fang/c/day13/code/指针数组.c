#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int compare(const void *p_value, const void *p_value1) { 
    //可以接受任何类型的指针,void*表示通用，具体什么类型需要自己去判断
    char ** pp_str = (char **)p_value;  //二级指针
    char ** pp_str1 = (char **)p_value1;
    return  strcmp(*pp_str, *pp_str1);
   }
int main(){
    int loop = 0;
    char *strs[5] = {"China","Russia","England","France","America"};//数组为5个指针构成
    qsort(strs, 5, sizeof(char *), compare);//第一个参数即数组首地址，数组中变量的地
    for(loop = 0;loop <= 4;loop++){
        printf("%s\n", strs[loop]);
    }
    //clear();
    //printf("\n");
    return 0;
}
