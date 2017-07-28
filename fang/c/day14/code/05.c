 /*
 * 文件练习
 * 复制
 */
#include <stdio.h>
int main(){
    FILE *p_file = NULL;            //文件类型指针
    FILE *p_file1 = NULL;
    p_file =  fopen("a.txt","r");   //当前文件路径,读
    if(p_file) {
        //文件操作语句
        p_file1 =  fopen("b.txt","w");   //当前文件路径，写
        if(p_file1) {
            char ch = 0;
            do {
                ch = fgetc(p_file);
                if(ch != EOF) {
                    fputc(ch, p_file1);
                }
            }while(EOF != ch);
            fclose(p_file1);
            p_file1 = NULL;
        }
        fclose(p_file);
        p_file = NULL;
    }
    return 0;
}
