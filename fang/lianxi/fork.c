#include <unistd.h>
#include <stdio.h>
int main(void){
    int i = 0;
    for (i = 0; i < 2; i++){
        fork();
        printf("%d: -\n", i);
    }
    sleep(5);
    return 0;
}
