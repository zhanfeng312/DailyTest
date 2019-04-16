#include <iostream>
#include <iomanip>
using namespace std;
const int N = 3;
class Matrix{
public:
    Matrix(int a[N][N]){
        //二维数组要依次赋值
        for (size_t i = 0; i < N;i++)
            for (size_t j = 0; j < N;j++)
                m_a[i][j] = a[i][j];
    }
    //重载<<操作符
    //全局友元实现
    friend ostream& operator << (ostream& os, Matrix& m){
        for (size_t i = 0; i < N;i++){
            for (size_t j = 0; j < N;j++)
                os << setw(3) << m.m_a[i][j]<< ' ';
            os << endl;
        }
        return os;
    }
    const Matrix operator + (const Matrix& m1){
        for (size_t i = 0; i < N; i++)
            for (size_t j = 0; j < N; j++)
                m_a[i][j] += m1.m_a[i][j];
        return Matrix(m_a);
    }
private:
    int m_a[N][N];
};
int main (void){
    int a[N][N] = {1, 2, 3,
                   4, 5, 6,
                   7, 8, 9};
    int b[N][N] = {1, 2, 3,
                   4, 5, 6,
                   7, 8, 9};
    Matrix m1(a), m2(b);
    Matrix m3(a);
    m3 = m1 + m2;
    cout << m3 << endl;
    return 0;
}
