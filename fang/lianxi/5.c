#include <stdio.h>
int main (){
    int a = 0, i;
    for (i = 2; i <= 5; i++){
        if (5 % i == 0){
            a++;
        }
    }
    printf("%d\n", a);

    return 0;
}
