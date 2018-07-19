#include <iostream>
#include <cstring>
using namespace std;
void reverse(char* src, char* dest){
    if (!src)
        return;
    size_t len = strlen(src);
    for (size_t i = 0; i < len;++i)
        dest[i] = *(src + len - 1 - i);
    dest[len] = '\0';
}
int main(void){
    char arr[] = "fang";
    char dest[10];
    reverse(arr, dest);
    cout << dest << endl;
    return 0;
}
