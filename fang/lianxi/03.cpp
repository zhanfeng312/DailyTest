#include <iostream>
#include <cstdio>
#include <time.h>
using namespace std;
int main (void){
    cout << "当前的系统时间为:"<< endl;
    while (true){
        fflush(NULL);
        time_t t = time(NULL);
        tm* lt = localtime(&t);
        printf("%02d:%02d:%02d\r", lt->tm_hour, lt->tm_min, lt->tm_sec);
        fflush(stdout);
        sleep(1);
    }
    return 0;
}
