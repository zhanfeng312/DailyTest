/*
 * 文件练习
 */
#include <stdio.h>
int main(){
    FILE *p_file = NULL;  //文件指针
    char str[] = "abcdef";
    int loop = 0;
    p_file = fopen("abc.txt","w");   //当前文件路径,写操作
    if(p_file) {
        //文件操作语句
        while(str[loop]) {
           if(EOF == fputc(str[loop], p_file))  //把单一的字符写在文件中
                break;
            loop++;
        }
        fclose(p_file);
        p_file = NULL;
    }
    return 0;
}
