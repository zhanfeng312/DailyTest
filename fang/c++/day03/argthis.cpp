#include <iostream>
using namespace std;
class Student;
class Teacher {
public:
    void educate(Student* s);   //从前往后编译
    void reply(const string& answer) {
        m_answer = answer;
    }
private:
    string m_answer;
};
class Student {
public :
    void ask(const string& question, Teacher* t) {
        cout << "问题:" << question << endl;
        t->reply("不知道.");
    }
};
    void Teacher::educate(Student* s) {   //从前往后编译
        s->ask("什么是this指针?", this);  //t的
        cout << "答案:" << m_answer << endl;
    }
int main(void){
    Teacher t;
    Student s;
    t.educate(&s);
    return 0;
}

