#include <stdio.h>
//#define ZHAOBENSHAN
int main(){
    int i = 0;
    printf("请输入你要点的菜的标号:(1:龙虾 2:小野鸡顿蘑菇)");
    scanf("%d", &i);
#if defined(ZHAOBENSHAN)  //条件表达式，如果前面定义过，表达式为
    switch(i) {
        case 1:
            printf("这个没有\n");
            break;
        case 2:
            printf("这个真没有\n");
            break;
    }
#else
        switch(i) {
        case 1:
            printf("请您稍等\n");
            break;
        case 2:
            printf("这个有，请您等等\n");
            break;
    }
#endif
    return 0;
}
