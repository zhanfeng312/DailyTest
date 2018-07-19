#include <stdio.h>
int main(void){
    /*int a = 100;  //十六进制形式
    printf("%#x\n", a);
    printf("%d\n", a);
    */
    int a = 100;
    //a = 200; 不能对常属性的变量赋值
    const int *p = &a;
    //*p = 200;
    int* const p1 = &a;
    unsigned int size1 = 5 ;
    char a1[size1];
    int b = 4;
//    (++b) += (b++);
    printf("%d\n", b);
    return 0;
}
