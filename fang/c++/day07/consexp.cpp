#include <iostream>
#include <stdexcept>
#include <cstdio>
using namespace std;
class FileError : public exception{ //继承自标准异常类,
//private:
    public:
    const char* what(void) const throw() {
        return "文件访问失败!";
    }
};
class B{
public:
    B (void) {
        cout << "B构造" << endl;
    }
    ~B(void) {
        cout << "B析构" << endl;
    }
};
class A {
public:
    A (void): m_b (new B) {
        FILE* fp = fopen("none", "r");
        if (! fp){
            delete m_b;
            throw FileError(); 
            //对象构造过程中,抛出的异常,对象称为不完整对象
        }
        //....
        //fclose(fp);
    }
private:
    B* m_b;
};
int main (void) {
    try {
        A a;
        //...
    }
    catch (exception& ex){
        cout << ex.what() << endl;
    }
    return 0;
}
