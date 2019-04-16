#include "cmp.h"
#include <iostream>
using namespace std;
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
