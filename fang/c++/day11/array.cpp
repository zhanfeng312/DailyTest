#include <iostream>
using namespace std;
template<typename T = int, size_t S = 5> //缺省,和函数的缺省参数一样
class Array {
public:
	T& operator[] (size_t i) {
		return m_array[i];
	}
	const T& operator[] (size_t i) const {
		return const_cast<Array&> (*this) [i];
	}
	size_t size (void) const {
		return S;
	}
	friend ostream& operator<< (ostream& os,
		const Array& arr) {
		for (size_t i = 0; i < arr.size (); ++i)
			os << '(' << arr.m_array[i] << ')';
		return os;
	}
private:
	T m_array[S];
};
int main (void) {
	const /*volatile*/ int x = 3, y = 7;
	Array<int, x+y> arr;// 必须算出字面值
	for (size_t i = 0; i < arr.size (); ++i)
		arr[i] = i;
	cout << arr << endl;
	Array<Array<int, 4>, 3> m;
	for (size_t i = 0; i < m.size (); ++i)
		for (size_t j = 0; j < m[i].size (); ++j)
			m[i][j] = i * m[i].size () + j;
	cout << m << endl;
	Array<double> a2; //缺省形参
	Array<> a3;
	return 0;
}
