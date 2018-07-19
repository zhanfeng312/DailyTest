#include <iostream>
#include <cstring>
using namespace std;
void func (char buf[], int n){
    int i(0);  //循环变量
    size_t len = strlen(buf);
    if (n <= len){
abc:
        char *pi = new char[n];  //申请n个内存空间
        for(i = 0; i < n; i++)    //把这n个挪出来
            *(pi + i) = buf[len-1-i];
        for(i = 0; i < len-n; i++) //把len -n 个右移
            buf[len-1-i] = buf[len-n-1-i];
        for(i = n;i > 0;i--)     //把n个赋给前面
            buf[n-i] = *(pi + i - 1);
        for (i = 0; i < len ; ++i)
            cout << buf[i];
        cout << endl;
        delete []pi;
    }
    else{
        n = n % len;
        goto abc;
    }
}
int main (void) {
    char buf[] = "abcdefghi";
    int m;
    cout<< "请输入你要循环右移的个数:";
    cin >> m;
    func(buf, m);
    return 0;
}
