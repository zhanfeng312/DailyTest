/
 *秒表练习
 */
#include <stdio.h>
#include <time.h>
#include <unistd.h>
int main(){
    int start = time(0);   //显示当前时间，要包括头文件time.h
    while(1){
        printf("秒表为:");
        printf("%ld\r",time(0) - start);
        fflush(stdout);
        sleep(1);
    }
    return 0;
}
