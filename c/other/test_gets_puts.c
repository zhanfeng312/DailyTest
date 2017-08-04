#include <stdio.h>

int main(){
    
    printf("start test\n");
    
    char a[10] = {0};
    char b[10] = {0};
    char c,d;
    
    scanf("%s",a);
    printf("a中保存的字符串为：%s\n",a);
    
    c=getchar();
    printf("c中保存的字符为：%c\n",c);
    
    gets(b);
    printf("b中保存的字符串为：%s\n",b);
    
    d=getchar();
    printf("d中保存的字符为：%c\n",d);
    
    puts("fang");
    
    return 0;
}
