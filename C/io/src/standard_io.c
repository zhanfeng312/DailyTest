#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFF_SIZE (64)
char g_buf[BUFF_SIZE] = {0};

void test_fgets(void)
{
    FILE *fp = NULL;
    char *p = NULL;
    int len = -1;

    if ((fp = fopen("b.txt", "r")) == NULL) { //不同的打开方式
        printf("b.txt not exist!\n");
        return;
    }

    while (1) {
        memset(g_buf, 0, sizeof(g_buf));
        if (fgets(g_buf, sizeof(g_buf), fp) == NULL) {
            if (feof(fp)) {
                printf("file read over\n");
                break;
            }
            if (ferror(fp)) {
                printf("fgets read error\n");
                break;
            }
        } else {
            if ((len = strlen(g_buf)) > 0 && *(g_buf + len - 1) == '\n') { //把最后的\n转换为\0
                *(g_buf + len - 1) = 0;
            }
            printf("%s\n", g_buf);
        }
    }
    fclose(fp);
    fp = NULL;
}

/*
format 转换说明组成是%[flags][width][.precision][length]specifier
*/
void test_printf(void) 
{
    /*
    flags：
    1、默认右对齐， 如果指定了负号(-)选项，则左对齐；
    2、前面加0，空位补0，如果出现了减号标志或者指定了精度，则忽略该标志
    3、如果指定宽度大于值的宽度， 按照指定宽度显示；否则忽略正常显示
    */
    int a = 11;
    int result = printf("[%4d]\n", a);  //默认右对齐
    printf("result is %d\n", result); //返回实际输出的字符数 7
    
    result = printf("[%04d]\n", a);  //默认右对齐
    printf("result is %d\n", result); //返回实际输出的字符数 7

    result = printf("[%-4d]\n", a); //- 表示左对齐
    printf("result is %d\n", result); //返回实际输出的字符数 7
  
    result = printf("[%+d]\n", a); //强制在结果之前显示加号或减号（+ 或 -）[+11]\n
    printf("result is %d\n", result);

    result = printf("[%*d]\n", 3, a); //等价于 printf("*%2d*\n",PAGES)
    printf("result is %d\n", result);
}

void test_scanf(void)
{
    printf("input content:\n");
    int a;
    float b;
    int result = scanf("%d %f", &a, &b); //返回读到的参数数目
    printf("result is %d\n", result);

    char c;
    do {
       scanf("%d", &a);
       int c1;
       while ((c1 = getchar()) != '\n' && c1 != EOF);
       //fflush(stdin);
       scanf("%c", &c);
       //fflush(stdin);
       while ((c1 = getchar()) != '\n' && c1 != EOF);
       printf("a=%d c=%c\n", a, c);
    } while (c != 'N');
}

void test_sscanf(void)
{
    char buf[512] = { 0 };
    int result = sscanf("123456 ", "%s", buf);
    printf("[%s]\n", buf); //[123456]
    printf("result is %d\n", result); //1

    sscanf("123456 ", "%4s", buf);
    printf("[%s]\n", buf); //[1234]

    sscanf("123456 abcdedf", "%[^ ]", buf);
    printf("[%s]\n", buf); //[123456]

    sscanf("123456abcdedfBCDEF", "%[1-9a-z]", buf);
    printf("[%s]\n", buf); //[123456abcdef]

    sscanf("123456abcdedfBCDEF", "%[^A-Z]", buf);
    printf("[%s]\n", buf); //[123456abcdedf]

    sscanf("iios/12DDWDFF@122", "%*[^/]%s", buf);
    printf("[%s]\n", buf); //[/12DDWDFF@122]

    sscanf("iios/12DDWDFF@122", "%*[^/]/%[^@]", buf);
    printf("[%s]\n", buf); //[12DDWDFF]

    sscanf("hello, world", "%*s%s", buf);
    printf("[%s]\n", buf); //[world]
}

int main(int argc, char *argv[])
{
    // printf("----------test printf-----------\n");
    // test_printf();

    // printf("----------test scanf------------\n");
    // test_scanf();

    printf("----------test sscanf----------\n");
    test_sscanf();

    // printf("----------test fgets----------\n");
    // test_fgets();

    getchar();

    return 0;
}
