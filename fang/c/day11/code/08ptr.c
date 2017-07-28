#include <stdio.h>
#define NEG(n)    n = 0 -  n
/*void neg(int value)
{
    value = 0 - value;
}*/
int main(){
    int value = 4;
    //neg(value);
    NEG(value);
    printf("value是%d\n",value);
    return 0;
}
