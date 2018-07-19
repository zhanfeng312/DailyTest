#include <stdio.h>
int main (){
    /*char *s[] = {"one", "two", "three"}, *p;
    p = s[1];
    printf("%c,%s\n", *(p+1), s[0]);
    */
    char *s = "abcde";
    s++;
    printf("%s\n", s);
    return 0;
}
