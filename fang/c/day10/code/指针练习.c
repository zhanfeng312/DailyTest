#include <stdio.h>
int main(){
    int a[] = {1,2,3,4,5};
    int *p_value;
    for(p_value = a;p_value <= (a + 4);p_value++){
        printf("%d ",*p_value);
    }
    printf("\n");
    return 0;
}
