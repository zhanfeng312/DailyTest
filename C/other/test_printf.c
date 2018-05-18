#include<stdio.h> 
#include<string.h> 
int main()
{
    char c = '\x41', s[20];
    int a = 1234;
    float f = 3.141592653589;
    double x = 0.12345678912345678;
    strcpy(s, "Hello,World");

    printf("a=%d\n", a);      //按照十进制整数格式输出，显示 a=1234
    printf("a=%d%%\n", a);    //输出%号 结果 a=1234%
    printf("a=%6d\n", a);     //输出6位十进制整数 左边补空格，显示 a= 1234
    printf("a=%06d\n", a);    //输出6位十进制整数 左边补0，显示 a=001234
    printf("a=%2d\n", a);     //a超过2位，按实际输出 a=1234
    printf("a=%-6d\n", a);    //输出6位十进制整数 右边补空格，显示 a=1234

    printf("\n\n");

    printf("f=%f\n", f);      //浮点数有效数字是7位，结果 f=3.141593
    printf("f=%6.4f\n", f);    //输出6列，小数点后4位，结果 f=3.1416
    printf("x=%lf\n", x);     //输出长浮点数 x=0.123457
    printf("x=%18.16lf\n", x);//输出18列，小数点后16位，x=0.1234567891234567

    printf("\n\n");

    printf("c=%c\n", c);      //输出字符 c=A
    printf("c=%#x\n", c);      //以十六进制输出字符的ASCII码 c=41

    printf("\n\n");

    printf("s[]=%s\n", s);    //输出数组字符串s[]=Hello,World
    printf("s[]=%6.9s\n", s); //输出最多9个字符的字符串 s[]=Hello,Wor

    printf("\n\n");

    printf("1=%d,2=%*d,3=%d\n", 1, 5, 3, 3);//5作为宽度控制

    int b = 0;

    scanf("%*c%d", &b);

    printf("%d\n", b);//输入123，输出23

    return 0;
}