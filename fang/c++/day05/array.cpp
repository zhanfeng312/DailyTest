#include <iostream>
using namespace std;
class Array {
public:
    Array (size_t size = 1) :
        m_data (new int[size]) {}
    ~Array (void) {
        if (m_data) {
            delete m_data;
            m_data = NULL;
        }
    }
    int& operator[] (size_t i) {//不能加const
        return m_data[i];
    }
    /*int& operator[] (size_t i) {
        return m_data[i];
    }
    const int& operator[] (size_t i) const {  //返回右值
        return m_data[i];
    }*/
    const int& operator[] (size_t i) const {  //重载关系
        return const_cast <Array&> (*this)[i];
    }
private:
    int* m_data;
};
int main(void) {
    Array arr (10);
    for (size_t i = 0;i < 10;++i)
        arr[i] = i;  // arr.operator[](i) = i;operator[] 是一个运算符
    //const Array& cr = arr;
    const Array& cr = arr;
    for (size_t i = 0;i < 10 ;++i)
        cout << cr[i] << ' ';
    cout << endl;
    cr[0]++;
    return 0;
}
