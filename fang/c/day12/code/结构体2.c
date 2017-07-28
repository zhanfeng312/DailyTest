#include <stdio.h>
typedef struct {
    int Chinese;
    int math;
    int English;
} stu;
void input(stu *p_r) {

    printf("请输入学生的三门成绩:");
    scanf("%d%d%d", &(p_r->Chinese), &(p_r->math), &(p_r->English));

}
void print(const stu *p_t){
    printf("语文成绩是%d\n",p_t->Chinese);
    printf("数学成绩是%d\n",p_t->math);
    printf("英语成绩是%d\n",p_t->English);

}
int main(){
    //stu student[3] = {{20, 30, 40},{30, 40, 50},{40, 50, 60}};
    stu student;
    input(&student);
    print(&student);

    return 0;
}
