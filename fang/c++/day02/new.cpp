#include <iostream>
using namespace std;
int main(void) {
    //int * pi = (int *)malloc(sizeof (int)); //pi为局部变量，存放在栈中，若不释放，内存泄漏
    //free(pi);
    int * pi = new int;
    *pi = 1000;
    cout << *pi << endl;
    delete pi;
    pi = NULL;
    /*
    *pi = 2000;
    cout << *pi << endl;
    */
    pi = new int[10];   //声明10个int型的数组
    for(size_t i = 0; i < 10;i++)
        pi[i] = i;
    for(size_t i = 0; i < 10;i++)
        cout << pi[i] << ' ';
    cout << endl;
    delete [] pi;   //以数组方式delete
    pi = NULL;
    pi = new int(1234);
    cout << *pi << endl;
    delete pi;
    pi = NULL;
    char buf[4] = {0x12, 0x34, 0x56, 0x78};
    pi = new (buf) int;    //定位new,这块不用delete,栈内存不用delete
    //delete pi;
    cout << (void *)pi << ' ' << (void *)buf << endl;
    cout << hex << *pi << endl;
    int (*p)[4] = new int[3][4];
    delete[] p;
    int(*q)[4][5] = new int[3][4][5];
    delete[] q;
    return 0;
}
