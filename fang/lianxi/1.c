#include <stdio.h>
union TEST_U{
    char str[4];
    int ivalue;
    long lvalue;
};
struct REST_S{
    union TEST_U a;
    int b;
}stTest;
int main (){
    /*printf("%d\n", sizeof (stTest));
    int i = 4%2.1;
    int len = 0;
    printf("fangzhao%n", &len);
    printf("\n");
    printf("%d\n", len);
    */
    size_t i = 1-2;
    printf("%d\n", i);
    return 0;
}
