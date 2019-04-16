/*
 * 文件练习
 */
#include <stdio.h>
int main(){
    FILE *p_file = NULL;  //文件类指针
    int values[] = {1, 2, 3, 4, 5};
    p_file =  fopen("a.bin","wb");   //当前文件路径
    if(p_file) {
        //文件操作语句
        int num = fwrite(values, sizeof(int), 5, p_file);//返回值表示变量的个数
        printf("共写入%d个整数变量\n", num);
        fclose(p_file);
        p_file = NULL;
    }

    return 0;
}
