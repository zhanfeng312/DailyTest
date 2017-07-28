#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cstdlib>
using namespace std;
#define BUFSIZE (1024*10)
int _xor (const char* src, const char* dst,
        unsigned char key){
    ifstream ifs(src, ios::binary); //读源文件
    if (! ifs){
        perror("打开源文件失败");
        return -1;
    }
    ofstream ofs (dst, ios::binary);
    if (! ofs){
        perror ("打开目标文件失败");
        return -1;
    }
    char* buf = NULL;
    try {
        buf = new char[BUFSIZE]; //可能会抛出异常
    }
    catch (bad_alloc& ex){
        cout << ex.what() << endl;
        return -1;
    }
    while (ifs.read(buf, BUFSIZE)){
        for (size_t i = 0; i < BUFSIZE; ++i)
            buf[i] ^= key;
        if(! ofs.write(buf, BUFSIZE)){
            perror ("写文件失败");
            return -1;
        }
    }
    if (! ifs.eof()){
        perror ("读取文件失败");
        return -1;
    }
    //有可能会因为前面中途退出,而使源文件没读完
    for (size_t i = 0; i < ifs.gcount(); ++i)
        buf[i] ^= key;
        if(! ofs.write(buf, ifs.gcount())){
            perror ("写文件失败");
            return -1;
        }
        delete[] buf;
        ofs.close();
        ifs.close();
        return 0;
}
//加密函数
int enc(const char* plain, const char* cipher){
    srand(time(NULL)); //随机数种子
    unsigned char key = rand() % 256;
    if (_xor (plain, cipher, key) == -1)
        return -1;
    cout << "密钥：" << (unsigned int)key << endl;
    return 0;
}
//解密函数
int dec (const char* cipher, const char* plain,
        unsigned char key){
    return _xor(cipher, plain, key);
}
//主函数
int main (int argc, char* argv[]){
    if (argc < 3){ //主函数控制逻辑
        cerr << "用法:" << argv[0]
            << "<明文文件> <密文文件>"
            << endl;
        cerr << "用法:" << argv[0]
            << "<密文文件> <明文文件> [<密钥>]"
            << endl;
        return -1;
    }
    if (argc < 4) //等于3的情况
        return enc(argv[1], argv[2]);
    else
        return dec(argv[1], argv[2], atoi(argv[3]));
    return 0;
}
