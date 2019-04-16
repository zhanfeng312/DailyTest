#include <string>
using namespace std;
//基于单链表的通讯录实现
class TongXun{
    public:
        TongXun(const string& num = "", 
                const string& name = "") : 
            m_num(num),m_name(name){}
        friend istream& operator >> (istream& is,
                TongXun& t){
            return is >> t.m_num >> m_name;
        }
        friend ostream& operator << (ostream& os,
                TongXun& t){
            return os << t.m_num << ' ' << m_name;
        }
    private:
        string m_num;
        string m_name;
};
bool add(list<TongXun>& li){
    string name, num;
    cout << "请输入name：" << endl;
    cin >> name;
    cout << "请输入num" << endl;
    cin >> num;
    li.push_back(TongXun(num, name));
}

