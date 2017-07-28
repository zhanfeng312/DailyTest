#include <iostream>
#include <cstring>
using namespace std;
class Stu{
    private:
        char *name;
    public:
        Stu(const char *p = "Noname")
        {
            name = new char[strlen(p)+1];
            strcpy(name, p);
            cout << "构造"<< name<< endl;
        }
        Stu(Stu& s)
        {
            name = new char[strlen(s.name)+1];
            strcpy(name, s.name);
            cout << "拷贝"<< name << endl;
        }
        ~Stu()
        {
            cout << "析构" << endl;
            delete name;
        }
};
Stu fn(Stu& a){
    Stu s("aaa");
    cout << "fn"<< endl;
    return s;
}
int main(void){
    //Stu& s = Stu("张三");
    //Stu d = Stu("李四");
    Stu s("张三");
    //Stu a(s);
    Stu d = fn(s);
    return 0;
}
