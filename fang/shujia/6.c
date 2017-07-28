#include <stdio.h>
int main(void){
    struct s{
        double d;
        short s;
        int i;
        char c;
    };
    printf("%d\n", sizeof(struct s));
    return 0;
}
