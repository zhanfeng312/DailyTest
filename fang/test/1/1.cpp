#include <iostream>
#include <list>
using namespace std;
const int M = 5;
const int N = 3;
int findLastRemain(int n, int m){
    if (n < 1 || m < 1)
        return -1;

    list<int> li;
    for (size_t i = 0; i < M;i++)
        li.push_back(i);
    size_t i = 0; //循环变量
    //迭代器变量
    typedef list<int>::iterator IT;
    IT current = li.begin();
    while (li.size() > 1){
        for (i = 1; i < m; i++){
            current++;
            if (current == li.end())
                current = li.begin();
        }
        IT next = ++current;
        if (next == li.end())
            next = li.begin();
        --current;
        li.erase(current);
        current = next;
    }
    return (*current);
}
int main (void){
    cout << "最后出去的人的序号为:" << findLastRemain(M, N)
        << endl;
    return 0;
}
