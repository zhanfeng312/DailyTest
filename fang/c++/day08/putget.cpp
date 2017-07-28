#include <iostream>
#include <fstream>
using namespace std;
int main(void){
    ofstream ofs("putget.txt");
    if (! ofs) {
        perror("打开文件失败");
        return -1;
    }
    for (char c = ' '; c <= '~'; ++c) //建议养成前++的习惯
        if(! ofs.put(c)){
            perror ("写入文件失败");
            return -1;
        }
    ofs.close();
    ifstream ifs("putget.txt");
    if (! ifs){
        perror ("打开文件失败");
        return -1;
    }
    char c;
    while((c = ifs.get()) != EOF) //EOF值一般是-1,表示读完/出错
        cout << c;

    if (! ifs.eof()){
        perror("读取文件失败");
        return -1;
    }
    cout << endl;
    ifs.close();
    return 0;
}
