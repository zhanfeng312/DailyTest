#include <iostream>
#include <cstring>
using namespace std;

class String {
public:
    String(const char *str = NULL) {
        cout << "construct" << endl;
        m_str = new char[strlen(str ? str : "") + 1];
        strcpy(m_str, str ? str : "");
    }

    ~String(void) {
        if (m_str) {
            cout << "deconstruct" << endl;
            delete[] m_str;
            m_str = NULL;
        }
    }

    String(const String& that) {
        cout << "copy construct" << endl;
        m_str = new char[strlen(that.m_str) + 1];
        strcpy(m_str, that.m_str);
    }

   /* void operator = (const String& that)
    {
        m_str = new char[strlen(that.m_str) + 1];
        strcpy(m_str, that.m_str);
    }*/

    String& operator =(const String& that) {
        cout << "assign" << endl;
        if (&that != this) {
            char *str = new char[strlen(that.m_str) + 1 ];

            delete[] m_str;

            m_str = strcpy(m_str, that.m_str);
        }
        return *this;
    }

    const char* c_str(void) const{
        return m_str;
    }
private:
    char *m_str;
};

int main(int argc, char *argv[])
{
    String s1("Hello World");
    cout << s1.c_str() << endl;

    String s2 = s1;
    cout << s2.c_str() << endl;

    String s3("Hello Linux");

    s1 = s3;
    cout << s1.c_str() << endl;

    return 0;
}