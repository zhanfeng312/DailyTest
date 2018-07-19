#include <stdio.h>
#include <stdlib.h>
#include "student.h"
extern student s[100];   //要使用.c文件声明的全局变量
extern int a;
int i,b,num;   //i为循环变量
FILE *p_file = NULL;
void menu() {
    printf("**********************************\n");
    printf("**********************************\n");
    printf("****欢迎进入学生信息管理系统******\n");
    printf("**    1:增加       2:删除       **\n");
    printf("**    3:查找       4:查看       **\n");
    printf("**    5:修改       6:排序       **\n");
    printf("**    7:查看文件   8:保存       **\n");
    printf("**    9:退出                    **\n");
    printf("**请选择操作序号(.............)***\n");
    printf("**********************************\n");
    printf("**********************************\n");
}
//选择排序
void sort()
{
    int i,j,k;
    student temp;
    for(i = 0;i < a-1;i++){
        k = i;
        for(j = i+1;j < a;j++)
            if(s[k].score > s[j].score)
                k = j;
        if(k != i){
            temp = s[k];
            s[k] = s[i];
            s[i] = temp;
        }
    }
    printf("排序后的学生信息为:(按C语言成绩)\n");
        listMessage();
}
void read()
{
    int count = 0;
    student s[100];
    p_file = fopen("b.txt", "rb");
    if(p_file) {
        printf("写入的文件中学生信息如下:\n");
        printf("学号\t姓名\t性别\t年龄\tC语言成绩:\n");
        for(i = 0;i < 100;i++){
            fread(&s[i], sizeof(student), 1, p_file);
            if(s[i].num == 0)
                break;
            printf("%d\t%s\t%c\t%d\t%g\n",s[i].num, s[i].m, s[i].gender, s[i].age, s[i].score);
            count++;
        }
        fclose(p_file);
        p_file = NULL;
        printf("文件中总共有%d个学生信息.\n", count);
    }
    else
        printf("当前没有那个文件,请输入后再查看!\n");
}
void save()
{
    p_file = fopen("b.txt", "ab");
    if(p_file){
        for(i = 0;i <= a - 1;i++){
            num = fwrite(&s[i], sizeof(student), 1, p_file);
            b++;
        }
        printf("本次共写入了%d个数据项\n", b);
        fclose(p_file);
        p_file = NULL;
    }
}
int main(){
    int shu_zi;   //选项以及循环变量
    menu();
    while(1){
        scanf("%d", &shu_zi);
        switch(shu_zi){
            case 1:
                //调用add函数
                addMessage();
                break;
            case 2:
                //调用del函数
                delMessage();
                break;
            case 3:
                //调用find函数
                findMessage();
                break;
            case 4:
                //调用list函数
                listMessage();
                break;
            case 5:
                rewriteMessage();
                break;
            case 6:
                sort();
                break;
            case 7:
                read();
                break;
            case 8:
                save();
                break;
            case 9:
                exit(0);
            default:
                printf("你输入的选项有误，请重新输入!\n");
                break;
        }
        menu();
    }
    return 0;
}
