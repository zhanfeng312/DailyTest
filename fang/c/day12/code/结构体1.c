/*
 * 结构体练习
 */
#include <stdio.h>
/*struct student{
    int age;
    char gender;
    float height;
    };
typedef struct student stu;     //给结构体变量起了个别名*/
typedef struct{         //student可写可不写
    int age;
    char gender;
    float height;
} stu;
int main(){
   /* struct student {        //struct stdent是一个变量类型,并不会产生新的变i量
        int age;
        char gender;
        float height;
    };
    struct student student;*/
   /* struct {
        int age;
        char gender;
        float height;
    } student;*/
    stu student1 = {24, 'F', 1.60f};  //按顺序初始化
    printf("年龄是%d\n",student1.age);
    printf("性别是%c\n",student1.gender);
    printf("身高是%g\n",student1.height);
    return 0;
}

