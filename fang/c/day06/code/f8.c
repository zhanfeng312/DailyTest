/*
 *强制类型转换
 */
#include <stdio.h>
int main(){
    int shu_zi = 300;
    printf("%d\n", (unsigned char)shu_zi);  //没有修改原来的数据类型
    printf("%d\n",shu_zi);
    return 0;
}
