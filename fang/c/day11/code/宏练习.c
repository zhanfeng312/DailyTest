#include <stdio.h>
# define MAX(m,n)    m > n ? m : n //宏参数不用写类型
int main(){
    printf("最大的数为:%d\n",MAX(3, 4));
    return 0;
}
