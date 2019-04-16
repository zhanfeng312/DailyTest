#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
int main(void){
    string s1 ("hello");
    //[]不会对下标检查，而at函数会对进行检查，会抛出异常
    //cout << s1.at(s1.length()+1) << endl;
    string s2 = "world";
    (s1 += " ") += s2;  //拼接
    cout << s1 << endl; //hello world
    string* str = new string("Hello Linux!");
    cout << *str << endl;
    getchar();
    string s3 = s1;
    cout << s3 << endl;  //hello world

    cout << (s1 == s3) << endl; //1
    
    s3[0] = 'H';
    cout << s3 << endl; //Hello world
    
    cout << (s1 > s3) << endl; //1
    cout << s1.length() << endl; //11
    cout << (s1 == s3) << endl; //0

    cout << (strcasecmp(s1.c_str(), s3.c_str()) == 0) << endl; //忽略大小写比较
    cout << sizeof(s1) << endl; //4

    FILE* fp = fopen("string.txt", "w");
    //fwrite(&s3, sizeof(s3), 1, fp);
    fwrite(s3.c_str(), sizeof(char), s3.length(), fp);
    fclose(fp);
    return 0;
}
