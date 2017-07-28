#include <iostream>
#include <iomanip>
using namespace std;
class Matrix {
public:
    Matrix (void) {
        for(size_t i = 0; i < 3; i++)
            for(size_t j = 0; j < 3; j++)
                m_arr[i][j] = 0;
    }
    Matrix (int a[][3]) {
        for (int i = 0; i < 3; i++)
            for (int j= 0; j < 3; j++)
                m_arr[i][j] = a[i][j];
    }
    Matrix operator+ (const Matrix& m) const {
        int a[3][3];
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
                a[i][j] = m_arr[i][j] + m.m_arr[i][j];
        return a;
    }
    Matrix operator- (const Matrix& m) const {
        int a[3][3];
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
                a[i][j] = m_arr[i][j] -  m.m_arr[i][j];
        return a;
    } 
    friend ostream& operator << ( ostream& os, const Matrix& m){
        for(size_t i = 0; i < 3; ++i){
            for (size_t j = 0; j < 3;++j)
                os << setw(4)<<m.m_arr[i][j];
            os<< endl;
        }
        return os;
    }
private:
    int m_arr[3][3];
};
int main(void){
    int a1[3][3] = {1,2,3,4,5,6,7,8,9};
    Matrix m1(a1);
    int a2[3][3] = {9,8,7,6,5,4,3,2,1};
    Matrix m2(a2);
    cout << "矩阵相加:" << endl;
    cout << m1 + m2 << endl << endl;
    return 0;
}
