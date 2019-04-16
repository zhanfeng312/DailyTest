#include <iostream>
#include <cstring>  //strlen是C中的函数
using namespace std;
class String {
public:
    String(const char* str = NULL) {   //构造函数
        m_str = new char[strlen (str ? str : "") + 1];
        strcpy(m_str, str ? str : "");  //连\0也拷贝
    }
    ~String(void){ //析构函数
        if(m_str){
            delete[] m_str;
            m_str = NULL;
        }
    }
    String(const String& that) {   //复制构造函数
        m_str = new char[strlen(that.m_str) + 1];  //申请空间
        strcpy(m_str, that.m_str);
    }
    /*
    void operator = (const String& that){  //拷贝赋值运算符
        m_str = new char[strlen(that.m_str)+1];
        strcpy(m_str, that.m_str);
    }
    */
    
    String& operator = (const String& that) {
        if(&that != this){   //防止自赋值
            /*小鸟
            delete[] m_str;
            m_str = new char[strlen(that.m_str)+1];  //new可能失败，引起异常
            strcpy(m_str, that.m_str);
            */
            /*大鸟
            char* str = 
                new char[strlen(that.m_str)+1];
            delete[] m_str;
            m_str = strcpy(str, that.m_str);
            */
            //老鸟
            String temp(that);   //复用了拷贝构造函数，显然简洁
            swap(m_str, temp.m_str);   //库函数
        }
        return *this;
    }
    const char* c_str (void) const {
        return m_str;
    }
private:
    char* m_str;
};
int main(void) {
    String s1("Hello, World!");
    cout << s1.c_str() << endl;
    String s2 = s1;
    cout << s2.c_str() << endl;
    String s3("Hello, Linux");
    try {
        s1 = s3;
    }
    catch (exception& ex) {
        cout << ex.what() << endl;
    }
    cout << s1.c_str() << endl;
    return 0;
}
