/*
 * 文件练习
 */
#include <stdio.h>
int main(){
    FILE *p_file = NULL;  //文件类指针
    p_file =  fopen("a.txt","r");   //当前文件路径
    if(p_file) {
        //文件操作语句
        fseek(p_file, 2, SEEK_SET);
        printf("%c ",fgetc(p_file));
        //rewind(p_file);
        fseek(p_file, 1, SEEK_CUR);
        printf("%c ",fgetc(p_file));
       // rewind(p_file);
        fseek(p_file, -3, SEEK_END);
        printf("%c ",fgetc(p_file));
        printf("\n");
        fclose(p_file);
        p_file = NULL;
    }

   return 0;
}
