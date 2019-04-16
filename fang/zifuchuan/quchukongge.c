#include <stdio.h>
#include <string.h>
void trim(char* inStr) {
    size_t i = 0, k = 0;
    size_t j = strlen (inStr) - 1;
    char s[20];
    while (inStr[i] == ' ' && inStr != '\0')
        i++;
    while (inStr[j] == ' ' && j >= 0)
        j--;
    while (i <= j)
        s[k++]= inStr[i++];
    s[k] = '\0';
    printf("%s\n", s);
}
int main (void) {
    char *s = " a d ";
    trim(s);
    return 0;
}
