#include <iostream>
#include <fstream>
using namespace std;
int main (void){
    fstream fs("seek.txt", ios::in | ios::out);
    if (! fs){
        perror("打开文件失败");
        return -1;
    }
    fs << "0123456789";
    cout << fs.tellp() << endl; //写位置在文件尾后面
    cout << fs.tellg() << endl;
    fs.seekp (-3, ios::cur);//向文件头位置移动3个位置
    fs << "XYZ";
    fs.seekg(4, ios::beg); //从文件头开始
    int i;
    fs >> i;
    cout << i << endl;
    cout << fs.tellg() << endl;
    cout << fs.tellp() << endl;
    fs.seekg(-6, ios::end); //从文件尾开始算,9的后面
    fs << "ABC";
    cout << endl;
    return 0;
}
