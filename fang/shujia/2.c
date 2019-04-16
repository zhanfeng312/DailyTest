#include <stdio.h>
int func (int n);
int main(void){
    printf("%d\n", sum(5));
    return 0;
}
int sum(int n){
    if (n == 1)
        return 1;
    else
        return(n + sum(n-1));
}
