#include <stdio.h>
#include <string.h>

#define BUFF_SIZE  (64)
char g_buf[BUFF_SIZE] = { 0 };

void print_buf(char *buf)
{
    printf("%s\n", buf);
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

}

int main(int argc, char *argv[])
{
    /*printf("-------------test gets!-----------\n");
    test_gets();*/

    /*printf("-------------test fgets-----------\n");
    test_fgets();*/

    /*printf("----------test scanf----------------\n");
     test_scanf();*/

     /*printf("------test sscanf---------------------\n ");
     test_sscanf();*/

    getchar();

    return 0;
}
