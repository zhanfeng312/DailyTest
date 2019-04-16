#include <stdio.h>
int main(){
    int shu_zi = -10;
    unsigned int shu_zi1 = 3;
    shu_zi = (shu_zi + shu_zi1) > 0 ? 1: 0;
    printf("计算结果是:%d\n",shu_zi);
    printf("大小是%d\n",sizeof (3 < 5 ? 1 : 0.9));


    return 0;
}
