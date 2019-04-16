/*
 * 递归函数练习
 */
#include <stdio.h>
void print(int num)
{                        //num表示还有多少次没打
    if(num == 1){
        printf("1\n");
    }
    else{
        printf("1\n");
        print(num - 1);
    }
}
int main(){
   // int num = 3;
    print(3);
    return 0;
}
