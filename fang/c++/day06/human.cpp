#include <iostream>
using namespace std;
class Human {
public:
    Human (const string& name, int age) :
        m_name (name), m_age(age) {}
    void who(void) const {
        cout << m_name << ", " << m_age << endl;
    }
    void eat (const string& food) const {
        cout << "我在吃" << food << endl;
    }
protected:          //属性只有本类和子类可以访问
    string m_name;
    int m_age;
};
class Student : public Human {  //Student类继承了Human类的成员
public:
    Student (const string& name, int age, int no) : //若没
       Human (name, age), m_no (no) {}
    Student& operator= (const Student& that) { //子类的拷贝赋值
        if (&that != this) {
            Human::operator= (that);
            m_no = that.m_no;
        }
        return *this;
    }
    void learn (const string& lesson) const {
        cout << "我(" << m_no <<")在学" << lesson << endl;
    }
    using Human::eat;
    void eat (void) const {
        cout << "我绝食" << endl;
    }
private:
    int m_no;
 };
int main(void) {
    Student s1("张飞", 25, 1001);
    s1.who();
    s1.eat("包子");   //作用域限定
    s1.learn("C++");
    Human* h1 = &s1; //子类对象的指针可以被隐式转换为基类类型的指针
    h1 -> who();
    h1 -> eat("KFC");
    //h1 -> learn("C");  //超过指针类型范围
    Student* ps = static_cast<Student*> (h1); //显示类型转换,
    ps -> learn("C");
    Student s3 ("赵云", 20, 1002);
    s3 = s1;
    s3.who ();
    s3.learn ("数学");
    return 0;
}
