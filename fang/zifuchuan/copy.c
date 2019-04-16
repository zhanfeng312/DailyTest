#include <stdio.h>
char* strcpy(char* dest, const char* src)
{
    if (!dest || !src)
        return NULL;
    char *temp = dest;
    while ((*dest++ = *src++) != '\0');
    return temp;
}
int main(void) {
    char *src = "fang";
    char dest[10];
    strcpy(dest, src);
    printf("%s\n", dest);
    return 0;
}
