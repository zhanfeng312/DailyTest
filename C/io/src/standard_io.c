#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFF_SIZE  (64)
char g_buf[BUFF_SIZE] = {0};

void print(char *buf)
{
    printf("%s\n", buf);
    printf("len is %ld\n", strlen(buf));
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
        } else {
            if ((len = strlen(g_buf)) > 0 && *(g_buf + len - 1) == '\n') {
                *(g_buf + len - 1) = 0;
            }
            print(g_buf);
        }
    }

    fclose(fp);
    fp = NULL;
}

void test_scanf(void)
{
#if 0
    printf("input content:\n");
    scanf("%*s%s", g_buf);//�������з�ֹͣ

    int a;
    char c;

    do
    {
       scanf("%d", &a);
       //ͨ�� while ѭ�����������е��������ݡ��ԡ�����
       //gcc ��fflush(stdin)������
       int c1;
       while ((c1 = getchar()) != '\n' && c1 != EOF);
       //fflush(stdin);
       scanf("%c", &c);
       //fflush(stdin);
       while ((c1 = getchar()) != '\n' && c1 != EOF);
       printf("a=%d   c=%c\n", a, c);
    } while (c != 'N');
#endif
}

void test_sscanf(void)
{
#if 0
	1��һ���÷�
		char buf[512] = { 0 };
		sscanf("123456 ", "%s", buf);
		printf("%s\n", buf);
		���Ϊ��123456
	2. ȡָ�����ȵ��ַ��������������У�ȡ��󳤶�Ϊ4�ֽڵ��ַ�����
		sscanf("123456 ", "%4s", buf);
		printf("%s\n", buf);
		���Ϊ��1234
	3. ȡ��ָ���ַ�Ϊֹ���ַ��������������У�ȡ�����ո�Ϊֹ�ַ�����
		sscanf("123456 abcdedf", "%[^ ]", buf);
		printf("%s\n", buf);
		���Ϊ��123456
	4. ȡ������ָ���ַ������ַ��������������У�ȡ������1��9��Сд��ĸ���ַ�����
		sscanf("123456abcdedfBCDEF", "%[1-9a-z]", buf);
		printf("%s\n", buf);
		���Ϊ��123456abcdedf
	5. ȡ��ָ���ַ���Ϊֹ���ַ��������������У�ȡ������д��ĸΪֹ���ַ�����
		sscanf("123456abcdedfBCDEF", "%[^A-Z]", buf);
		printf("%s\n", buf);
		���Ϊ��123456abcdedf
	6������һ���ַ���iios / 12DDWDFF@122����ȡ / �� @ ֮����ַ������Ƚ� "iios/"���˵����ٽ���'@'��һ�������͵�buf��
		sscanf("iios/12DDWDFF@122", "%*[^/]/%[^@]", buf);
		printf("%s\n", buf);
		���Ϊ��12DDWDFF
	7������һ���ַ���"hello, world"��������"world"����ע�⣺������֮����һ�ո�
		sscanf("hello, world", "%*s%s", buf);
		printf("%s\n", buf);
		���Ϊ��world
	%*s��ʾ��һ��ƥ�䵽��%s�����˵�����hello�������ˣ����û�пո�����ΪNULL��
#endif
}

void test_file(void)
{
    FILE *fp = NULL;
    const char *fileName = "fang.txt";

    fp = fopen(fileName, "a+");
    if (fp == NULL) {
        printf("file not exist\n");
        exit(1);
    }

    char buf[] = "Juan\nFang";
    size_t num = fwrite(buf, 1, sizeof(buf), fp);
    printf("res is %ld\n", num);

    fclose(fp);
    fp = NULL;
}

int main(int argc, char *argv[])
{
    test_file();

    printf("--------- test fgets-----------\n");
    test_fgets();

    printf("----------test scanf-----------\n");
    test_scanf();

    printf("----------test sscanf----------\n");
    test_sscanf();

    getchar();

    return 0;
}
