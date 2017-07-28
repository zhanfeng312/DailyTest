#include <iostream>
using namespace std;
bool func(string& s){
    size_t len = s.length();
    int i = 0, j = len-1;
    for(;i <= j;){
        //string类也支持下标访问
        if (s.at(i++) == s.at(j--))
            continue;
        else
            return false;
    }
    return true;
}
int main (void){
    string s;
    cout << "请输入一个数字字符串:";
    cin >> s;
    if(func (s))
        cout << "是" << endl;
    else
        cout << "不是" << endl;
    return 0;
}
