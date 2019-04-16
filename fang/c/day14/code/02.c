/*
 * 文件练习
 */
#include <stdio.h>
int main(){
    FILE *p_file = NULL;  //文件类指针
    p_file =  fopen("a.txt","w");   //当前文件路径
    if(p_file) {
        //文件操作语句
        fclose(p_file);
        p_file = NULL;
    }

    return 0;
}
