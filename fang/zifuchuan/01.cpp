#include <iostream>
using namespace std;
int func(char* p1, char* p2){
    if (!p1 || !p2){
        cout << "字符串为空!" << endl;
        return -1;
    }
    int count = 0;
    while (*p1 != '\0' && *p2 != '\0'){
        if (*p1 == *p2 ||(*p1+32) == *p2 || (*p1-32) == *p2){
            count++;
            p1++;
            p2++;
        }
        else
            return count;
    }
    cout << "两个字符串相等,没有不同的字符!" << endl;
    return -1;
}
int main(void){
    char* p1 = "fang"; 
    char* p2 = "fbng";
    int index = func(p1, p2);
    cout << "第一个不同字母的位置为:"
         << index << endl;
    return 0;
}
