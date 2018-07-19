#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <sstream> //字符串流
using namespace std;
int main (void){
    cout << sqrt(2) << endl;
    cout.precision (10); //10位有效数字
    cout << sqrt(2) * 100 << endl;
    cout << setprecision (5) << sqrt(2) << endl
        << sqrt(2) * 100 << endl;
    cout << "当前精度:" << cout.precision() << endl;
    cout << setprecision(2) << 1.24 << ' ' << 1.25
        << ' ' << 1.26 << endl; //大于5往上入,区别
    cout << showbase << hex << 127 << endl;
   cout << oct << 127 << endl; //八进制
    cout << dec << 127 << endl; //十进制
    cout << noshowbase << hex << 127 << dec << endl;
    cout << setw(12) << 127 << 721 <<  endl;//默认靠右,setw只管一次
    cout << setfill ('$') << left << setw(12) << 127
        << endl; //填充字符,靠左对齐
    cout.precision(10);
    cout.setf (ios::scientific);
    cout << sqrt (2) << endl;
    cout.setf(ios::fixed);
    cout << sqrt(2) << endl;
    cout << 12.00 << endl;  //只打印12
    cout << showpoint << 12.00 << endl;
    cout << noshowpoint << 12.00 << endl;
    ifstream ifs ("stream.txt");
    ifs.unsetf(ios::skipws); //不跳过空白
    char c;
    while (ifs >> c)  //一个一个读,当分隔符处理
        cout << c;
    ifs.setf(ios::skipws); //跳过空白
    ifs.clear(); //复位
    ifs.seekg (ios::beg);
    while (ifs >> c)
        cout << c;
    ifs.close();
    cout << endl;
    int i = 1234;
    double d = 56.78;
    string s = "tarena";
    ostringstream oss;
    oss << i << ' ' << d << ' ' << s;//输入到字符串流中
    string str = oss.str(); //得到一个字符串
    cout << str << endl;
    str = "hello 3.14 pai";
    istringstream iss;
    iss.str(str);
    iss >> s >> d >>
    return 0;
}
