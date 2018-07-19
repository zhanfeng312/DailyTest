#ifndef __STUDENT_H__
#define __STUDENT_H__
typedef struct {
    int num;
    char m[30];
    char gender;
    int age;
    float score;
} student;
int a;
void addMessage();
void delMessage();
void rewriteMessage();
void findMessage();
void listMessage();
#endif
