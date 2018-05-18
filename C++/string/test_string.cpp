#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <iostream>
using namespace std;


string getMAC(string device)
{
    char aMAC[24] = { 0 };

    sleep(2);

    string str = aMAC;

    return str;
}

void test_getMAC()
{
    printf("start call getMAC!\n");

    std::string result = getMAC("haha");

    printf("the result is %s,address is %p\n", result.c_str(), result.c_str()));

    char *ret = strdup((char*)result.c_str());

    printf("ret is %p\n", ret);

    if (NULL != ret) {
        free(ret);
    }
}

void test_string()
{
    const char *str1 = "fang";
    string s1 = str1;
    cout << s1 << ":" << s1.size() << ":" << s1.length() << endl;

    string s2 = "fangzhf";
    const char *str2 = s2.c_str();
    printf("%s\n", str2);
}

int main (int argc, char **argv){
    
    //test_string();

    test_getMAC();

    return 0;
}