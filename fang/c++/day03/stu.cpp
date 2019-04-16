#include <iostream>
using namespace std;
class A{
public:
    A(int a){}
};
class Student {   //定义类
private:   //访问控制属性
    string m_name;
    int m_age;
    A m_a;
public:
    void eat(const string& food){
        cout << m_age << "岁的" << m_name 
             << "同学正在吃"<< food <<"."<<endl;
    }
   /* void _ZN7Student3eatERKSs (Student* this,
            const string& food) {
        cout <<this-> m_age << "岁的" << this->m_name 
             << "同学正在吃"<< food <<"."<<endl;
    }*/

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
    //构造函数
    Student(const string& name, int age): m_a(100){
        m_name = name;
        m_age = age;
        
    }
    //无参构造
    Student (void): m_a(100){
        m_name = "没名";
        m_age = 0;
    }
    //单参构造
    Student(const string& name): m_name(name),m_age(0),m_a(100) {}
};
int main(void){
    Student s1("张飞",25);
    s1.eat("包子");
    //_ZN7Student3eatERKSs (&s1, "包子")
    Student s2 = Student("赵云", 22);
    s2.eat("烧饼");
    //_ZN7Student3eatERKSs (&s2, "包子")
    Student s3;
    s3.eat("炒面");
    Student* s4 = new Student("关羽", 30);
    s4->eat("烤鸭");
    delete s4;
    Student& s5 = *new Student();
    s5.eat("面条");
    delete &s5;
    Student sa1[3] = {s1, s2};
    sa1[0].eat("KFC");
    sa1[1].eat("KFC");
    sa1[2].eat("KFC");
    Student* sa2 = new Student[3];
    sa2[0].eat("KFC");
    sa2[1].eat("KFC");
    sa2[2].eat("KFC");
    delete[] sa2;
    Student s6("刘备");
    s6.eat("拉条");
    return 0;
}
