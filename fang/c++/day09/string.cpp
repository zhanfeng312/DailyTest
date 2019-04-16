#include <iostream>
#include <cstring>
using namespace std;
//自定义的String类
class String {
public:
    //构造函数
    String (const char* str = NULL){
        m_str = new char[strlen ( str ? str : "") + 1];
        strcpy(m_str, str ? str : "");
    }
    //析构函数
    ~String(void){
        if (m_str){
            delete[] m_str;
            m_str = NULL;
        }
    }
    //拷贝构造
    String (const String& that){
        m_str = new char[strlen (that.m_str) + 1];
        strcpy(m_str, that.m_str);
    }
    //赋值运算符
    String& operator = (const String& that){
        //防止自赋值
        if (&that != this){
            //释放掉当前m_str的空间，因为要重新给它赋值
            delete[] m_str;
            m_str = new char[strlen (that.m_str) + 1];
            if (!m_str)
                throw "申请内存失败!";
            strcpy(m_str, that.m_str);
        }
            /*String temp(that);
            swap(m_str, temp.m_str);
            */
        return *this;
    }
    const char* c_str(void) const{
        return m_str;
    }
private:
    char* m_str;
};
int main (void){
    String s1("fang");
    cout << s1.c_str() << endl;
    String s2("zhao");
    cout << s2.c_str() << endl;
    try{
        s2 = s1;
    }
    catch (exception& ex){
        cout << ex.what() << endl;
    }
    cout << s2.c_str() << endl;
    return 0;
}
