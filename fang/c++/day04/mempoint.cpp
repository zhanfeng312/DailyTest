#include <iostream>
using namespace std;
class Student{
public:
    string m_name;
    int m_age;
};
int main(void) {
    string Student::*pname = &Student::m_name;
    int Student::*page = &Student::m_age;
    Student s("张飞", 25), *p = &s;
    return 0;
}

