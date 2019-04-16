#include <stdio.h>
#define STR(n)  #n
#define PTR(n)  p_##n
int main(){
    int *PTR(value) = NULL;
    printf("STR(3 + 6)是%s\n", STR(3 + 6));

    return 0;
}

