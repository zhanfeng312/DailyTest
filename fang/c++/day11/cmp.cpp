#include <iostream>
#include <cstring>
using namespace std;
//通用模板
template <typename T> //类型形参表
class Comparator{
    public:
        Comparator(T x, T y):
            m_x(x), m_y(y){}
        T min (void) const{
            return m_x < m_y ? m_x : m_y;
        }
        T max (void) const{
            return m_x > m_y ? m_x : m_y;
        }
    private:
        T m_x;
        T m_y;
};
//针对char*的全模板特化,有时没必要把全类特化
/*template <>
class Comparator<char*>{
    public:
        Comparator(char* x, char* y):
            m_x(x), m_y(y){}
        char* min (void) const{
            return strcmp(m_x,  m_y) < 0 ? m_x : m_y;
        }
        char* max (void) const{
            return strcmp(m_x, m_y) > 0 ? m_x : m_y;
        }
    private:
        char* m_x;
        char* m_y;
};
*/
//针对char*的成员函数特化
template<>
char* Comparator<char*>::min(void) const{
    return strcmp(m_x, m_y) < 0 ? m_x : m_y;
}
template<>
char* Comparator<char*>::max(void) const{
    return strcmp(m_x, m_y) > 0 ? m_x : m_y;
}

int main (void){
    cout << "输入两个整数:" << endl;
    int nx, ny;
    cin >> nx >> ny;
    Comparator<int> cn(nx, ny); //类模板无法猜，Comparator不是类,而是类模板
    cout << "最小值:"<< cn.min() << endl;
    cout << "最大值:"<< cn.max() << endl;
    
    cout << "请输入两个字符串:" << endl;
    char cx[256], cy[256];
    cin >> cx >> cy;
    Comparator<char*> cc(cx, cy);
    cout << "最小值:"<< cc.min() << endl;
    cout << "最大值:"<< cc.max() << endl;
    
    return 0;
}
