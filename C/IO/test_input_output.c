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
    //gets ����û����������ȡ���ȣ�һ�㲻��
    //gets()�����������з�('\n')��ȡ����֮������'\0'��β��

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
    scanf("%*s%s", g_buf);//�������з�ֹͣ
    print_buf(g_buf);

    //int a;
    //char c;

    //do
    //{
    //    scanf("%d", &a);
    //    //ͨ�� while ѭ�����������е��������ݡ��ԡ�����
    //    //gcc ��fflush(stdin)������
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
	PS. %*s��ʾ��һ��ƥ�䵽��%s�����˵�����hello�������ˣ����û�пո�����ΪNULL��
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
