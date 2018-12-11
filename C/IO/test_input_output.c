#include <stdio.h>
#include <string.h>

#define BUFF_SIZE  (64)
char g_buf[BUFF_SIZE] = { 0 };

void print_buf(char *buf)
{
    printf("%s\n", buf);
    printf("len is %d\n", strlen(buf));
}

void test_gets(void)
{
   gets(g_buf);
    //gets 函数没有限制它读取长度，一般不用
    //gets()函数丢弃换行符('\n')，取而代之的是以'\0'结尾。

    print_buf(g_buf);

    printf("buf is %s, len is %d\n", g_buf, strlen(g_buf));
}

void test_fgets(void)
{
    FILE *fp = NULL;
    char *p = NULL;
    int len = -1;

    if ((fp = fopen("b.txt", "r")) == NULL) {
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
        }
        else {
            if ((len = strlen(g_buf)) > 0 && *(g_buf + len - 1) == '\n') {
                *(g_buf + len - 1) = 0;
            }
            print_buf(g_buf);
        }
    }

    fclose(fp);
    fp = NULL;
}

void test_scanf(void)
{
    printf("input content:\n");
    scanf("%*s%s", g_buf);//遇到换行符停止
    print_buf(g_buf);

    //int a;
    //char c;

    //do
    //{
    //    scanf("%d", &a);
    //    //通过 while 循环把输入流中的余留数据“吃”掉：
    //    //gcc 中fflush(stdin)不好用
    //    int c1;
    //    while ((c1 = getchar()) != '\n' && c1 != EOF);
    //    //fflush(stdin);
    //    scanf("%c", &c);
    //    //fflush(stdin);
    //    while ((c1 = getchar()) != '\n' && c1 != EOF);
    //    printf("a=%d   c=%c\n", a, c);
    //} while (c != 'N');
}

void test_sscanf(void)
{
#if 0
	1、一般用法
		char buf[512] = { 0 };
		sscanf("123456 ", "%s", buf);
		printf("%s\n", buf);
		结果为：123456
	2. 取指定长度的字符串。如在下例中，取最大长度为4字节的字符串。
		sscanf("123456 ", "%4s", buf);
		printf("%s\n", buf);
		结果为：1234
	3. 取到指定字符为止的字符串。如在下例中，取遇到空格为止字符串。
		sscanf("123456 abcdedf", "%[^ ]", buf);
		printf("%s\n", buf);
		结果为：123456
	4. 取仅包含指定字符集的字符串。如在下例中，取仅包含1到9和小写字母的字符串。
		sscanf("123456abcdedfBCDEF", "%[1-9a-z]", buf);
		printf("%s\n", buf);
		结果为：123456abcdedf
	5. 取到指定字符集为止的字符串。如在下例中，取遇到大写字母为止的字符串。
		sscanf("123456abcdedfBCDEF", "%[^A-Z]", buf);
		printf("%s\n", buf);
		结果为：123456abcdedf
	6、给定一个字符串iios / 12DDWDFF@122，获取 / 和 @ 之间的字符串，先将 "iios/"过滤掉，再将非'@'的一串内容送到buf中
		sscanf("iios/12DDWDFF@122", "%*[^/]/%[^@]", buf);
		printf("%s\n", buf);
		结果为：12DDWDFF
	7、给定一个字符串"hello, world"，仅保留"world"。（注意：“，”之后有一空格）
		sscanf("hello, world", "%*s%s", buf);
		printf("%s\n", buf);
		结果为：world
	PS. %*s表示第一个匹配到的%s被过滤掉，即hello被过滤了，如果没有空格则结果为NULL。
#endif
}

int main(int argc, char *argv[])
{
    /*printf("-------------test gets!-----------\n");
    test_gets();*/

    /* printf("-------------test fgets-----------\n");
     test_fgets();*/

    /*printf("----------test scanf----------------\n");
    test_scanf();*/

     /*printf("------test sscanf---------------------\n ");
     test_sscanf();*/

    getchar();

    return 0;
}
