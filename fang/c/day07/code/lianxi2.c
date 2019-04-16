#include <stdio.h>
int main(){
    int xun_huan = 0;
    for (xun_huan = 1;xun_huan <= 9;xun_huan++){
       if(xun_huan == 3){
            continue;    //跳过其他部分，直接到大括号的末尾
       }
       else if (xun_huan == 6){
            break;    //立刻中止循环的执行
        }
       printf("%d\n",xun_huan);
    }

    return 0;
}
