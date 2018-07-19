#include <stdio.h>
int main (void) {
    char a, b, c;
    scanf("%c%*c%c%*c%c", &a, &b, &c);
    printf("%c %c %c\n", a, b, c);
    return 0;
}
