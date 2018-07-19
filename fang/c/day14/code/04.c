/*
 * 文件练习
 */
#include <stdio.h>
int main(){
    FILE *p_file = NULL;  //文件指针
    p_file =  fopen("a.txt","r");   //当前文件路径
    if(p_file) {
        //文件操作语句
        char ch = 0;
        do{
            ch = fgetc(p_file);
            if(EOF != ch) {
                printf("%c",ch);
            }
        } while(EOF != ch);
        printf("\n");
        fgetc(p_file);
        fclose(p_file);
        p_file = NULL;
    }

    return 0;
}
