#include <iostream>
using namespace std;
class Student {   //定义类
private:    //访问控制属性
    string m_name;
    int m_age;
public:
    void eat(const string& food){
        cout << m_age << "岁的" << m_name 
             << "同学正在吃"<< food <<"."<<endl;
    }
    void setName(const string& name){
        if(name == "2")
            cout << "你才"<<name <<"!"<<endl;
        else
            m_name = name;
    }
    void setAge(int age){
        if(age < 0)
            cout << "无效的年龄" << endl;
        else
            m_age = age;
    }

};
int main(void){
    Student student;
   // student.m_name = "2";
    //student.m_age = 25;
    /*student.setName("2");
    student.setAge(-100);*/
    student.setName("张飞");
    student.setAge(20);
    student.eat("包子");

    return 0;
}
