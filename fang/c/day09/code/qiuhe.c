#include <stdio.h>
int sum (int num) {
    if (num == 1)
        return 1;
    else 
        return num + sum(num - 1);
}
int main (){
    int value = sum (10);
    printf("value = %d\n", value);
    return 0;
}
