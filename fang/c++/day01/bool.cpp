/*只存1或0*/
#include <iostream>
using namespace std;
void print(bool sex)
{
    if(sex)
        cout << "男生" << endl;
    else
        cout << "女生!" << endl;
}
int main(void){
    bool b = true;
    cout << sizeof(b) << endl;
    cout << b << endl;
    b = false;
    cout << b << endl;
    b = 3.14;
    cout << b << endl;
    char *p = NULL;
    b = p;
    cout << b << endl;  //b = 0
    cout << boolalpha << b << endl; //输出true/false，而不是1/0
    bool sex;
    sex = 3;
    print(sex);
    return 0;
}
