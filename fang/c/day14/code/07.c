/*
 * 文件练习
 */
#include <stdio.h>
int main(){
    FILE *p_file = NULL;  //文件类型指针
    int values[5] = {0};
    int loop = 0;
    p_file = fopen("a.bin","rb");   //当前文件路径
    if(p_file) {
        //文件操作语句
        int num = fread(values, sizeof(int), 5, p_file);
        //返回值表示读出了几个变量
        printf("共读出%d个整数变量\n",num);
        for(loop = 0;loop <= 4;loop++) {
            printf("%d ", values[loop]);
        }
        printf("\n");
        fclose(p_file);
        p_file = NULL;
    }

    return 0;
}
