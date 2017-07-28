#include <iostream>
#include <cstring>  //strlen是C中的函数，所以要用到c中的string头文件
using namespace std;
class String {  //自定义String类
public:
    //构造函数
    String(const char* str = NULL) {
        m_data = new char[strlen (str ? str : "") + 1];
        strcpy(m_data, str ? str : "");  //连\0也拷贝
    }
    //析构函数
    ~String(void){
        if(m_data){
            delete[] m_data;
            m_data = NULL;
        }
    }
    //拷贝构造函数
    String(const String& that) {
        m_data = new char[strlen(that.m_data) + 1];  //申请空间
        strcpy(m_data, that.m_data);
    }
    //拷贝赋值运算符
    String& operator = (const String& that){
        m_data = new char[strlen(that.m_data)+1];
        strcpy(m_data, that.m_data);
        return *this;
    }
    const char* c_str (void) const {
        return m_data;
    }
private:
    char* m_data;
};
int main(void) {
    String s1("Hello, World!");
    cout << s1.c_str() << endl;
    String s2 = s1;
    cout << s2.c_str() << endl;
    String s3("Hello, Linux");
    s1 = s3;
    cout << s1.c_str() << endl;
    return 0;
}
