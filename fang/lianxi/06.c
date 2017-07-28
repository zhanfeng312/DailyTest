#include <stdio.h>
int main(void){
    //printf("%u\n", -1);
    int a = 3;
    //char* p = (char*)&a;
    //printf("%d\n", *p);
    float f = 3.1435;
    printf("%.3f\n", f);//小数位为3位，四舍五入原则
    printf("%04d\n", a);//占四列，不够四列用0补满
    printf("%*d\n", 4, a);//表示在第四列打印数字a
    return 0;
}
