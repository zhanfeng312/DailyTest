/*/*
 *联合练习
 
#include <stdio.h>
typedef union {
    char ch[4];
    int value;
} un;
int main(){
    un u;
    u.value = 0x12345678;
     if( 0x78 == u.ch[0]){
      printf("小端\n");
     }
    else{
      printf("大端\n");
    }
    printf("联合的大小是%d\n",sizeof(un));
    
    return 0;
}*/
/*
 * 枚举练习
 */
#include <stdio.h>
int main(){
   typedef enum {SPR, SUM, AUT, WIN} season;      //把要列举的先写出来
    printf("SPR是%d\n", SPR);       //第一个为0，其余的递推
    season s = AUT;                 //s变量就是整数类型变量
    printf("season是%d\n", s);       

    return 0;
}

