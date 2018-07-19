#include <stdio.h>
#include <string.h>
int main (void){
    FILE* fp = fopen("a.txt", "w+");
    if (! fp){
        return -1;
    }
    char arr[10] = "fang";
    printf("%s\n", arr);
    fwrite(arr, 1, strlen(arr), fp);
    fclose(fp);
    char str[] = "http://www.delta.com/";
    char* p = str;
    printf("%d\n", sizeof (p));
    printf("%d\n", sizeof (str));
    return 0;
}
