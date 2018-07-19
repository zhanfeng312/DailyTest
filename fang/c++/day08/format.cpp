#include <iostream>
#include <fstream> //文件流
using namespace std;
int main (void){
    ofstream ofs("format.txt"); //没有则创建,有则覆盖
    if (! ofs){
        perror("打开文件失败");
        return -1;
    }
    ofs << 1234 << ' ' << 56.78 << ' ' << "tarena"
        << '\n';
    ofs.close();
    ofs.open("format.txt", ios::app); //追加方式打开
    if(! ofs){
        perror("打开文件失败");
        return -1;
    }
    ofs << "append_a_line\n";
    ofs.close();
    ifstream ifs("format.txt");  //以r模式读文件
    if(! ifs){
        perror("打开文件失败");
        return -1;
    }
    int i;
    double d;
    string s1, s2;
    ifs >> i >> d >> s1 >> s2;
    cout << i << ' ' << d << ' ' << s1 << ' ' << s2<< endl;
    ifs.close();
    return 0;
}
