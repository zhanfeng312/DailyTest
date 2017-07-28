#include <iostream>
using namespace std;
struct Student {
    char name[128];
    int age;
    void who(void) {
        cout << "我叫" << name<< ",今年" << age << "岁了." << endl;
    }
};
int main(void){
    Student student = {"张飞",25},*ps = &student;
    student.who();
    ps->who();
    struct A{};
    cout << sizeof(A) << endl;
    


    return 0;
}
