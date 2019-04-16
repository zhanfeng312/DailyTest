#include <stdio.h>
#include "student.h"
student s[100];
int a;   //记录学生个数
/*定义addMessage函数*/
void addMessage(){    
    if(a > 100){
        printf("空间已占满!\n");
    }
    else{
        printf("请输入学生学号:");
        scanf("%d", &(s[a].num));
        printf("请输入姓名:");
        //fgets(s[a].m, 10, stdin);,为啥不用fgets函数，还有一定要加清空
        scanf("%s",s[a].m);
        scanf("%*[^\n]");
        scanf("%*c");
        printf("请输入性别:");
        scanf("%c", &(s[a].gender));
        printf("请输入年龄和C语言成绩:");
        scanf("%d%f", &(s[a].age), &(s[a].score));
    }
        a++;
}
void rewriteMessage()
{
    if (a == 0){
        printf("当前结构体数组为空，不能删除!\n");
    }
    int m,loop = 0,score;
    printf("请输入要修改的学生的学号:");
    scanf("%d", &m);
    for(loop = 0;loop < a;loop++){
        if(s[loop].num == m){
            printf("请输入修改后的成绩:");
            scanf("%d", &score);
            s[loop].score = score;
        }
    }
}
/*定义delMessage函数*/
void delMessage() {
    int m,loop;     //删除的位置，和循环变量
    if(a == 0) {
        printf("当前结构体数组为空，不能删除!\n");
    }
    else {
        printf("请输入要删除学生的学号:");
        scanf("%d", &m);
        for(loop = 0;loop < a;loop++){
            if(s[loop].num == m){
                for(loop = loop;loop < a;loop++)
                    s[loop] = s[loop+1];
            }
        }
        printf("删除成功!\n");
        a--;
    }   
}
/*定义findMessage函数*/
void findMessage() {
    int m = 0,loop;          //查找的学生学号
    if(a == 0){
        printf("当前结构体数组为空,不能进行查找!\n");
    }
    else{
        printf("请输入你要查找的学生学号:");
        scanf("%d", &m);
        for(loop = 0;loop < a;loop++)
            if(s[loop].num == m){
                printf("所要查找的学生信息如下:\n");
                printf("学号\t姓名\t性别\t年龄\tC语言成绩\n");
                printf("%d\t%s", s[loop].num, s[loop].m);
                printf("\t%c\t%d\t%g\n", s[loop].gender,s[loop].age, s[loop].score);
            }
    }
}
/*定义listMessage函数*/
void listMessage(){
    int loop = 0;
    if(a == 0)
        printf("当前学生信息为空,请输入后再查看!\n");
    else {
        printf("所有学生的信息如下:\n");
        printf("学号\t姓名\t性别\t年龄\tC语言成绩\n");
        for(loop = 0;loop <= a-1;loop++) {
            if(s[loop].num == 0)
                break;
            else{
                printf("%d\t%s", s[loop].num, s[loop].m);
                printf("\t%c\t%d\t%g\n", s[loop].gender,s[loop].age, s[loop].score);
            }
        }
    }
}
