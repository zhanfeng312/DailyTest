#include <stdio.h>
#include <string.h>
int main (void){ 
    /*char a = -5;
    printf("%d\n", (a << 3));
    printf("%d\n", a);
    char* arr = "fang";
    fputs(arr, stdout);
    printf("\n");
    char b[20];
    bzero(b, sizeof (b));
    fprintf(stdout, "%s\n", "zhao");
    */
    int a = 0, b = 1, c = 0;
    printf("%d\n", sizeof (a + b));
    printf("%d\n", c);
    double d = 1.004567886432456786532245;
    d++;
    printf("%lf\n", d);
    return 0;
}
