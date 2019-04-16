# include <stdio.h>
int main(){
    int shu_zi = 3,shu_zi1 = 7,shu_zi2 = 0;
    printf("%d %d %d\n",shu_zi,shu_zi1,shu_zi2);

    shu_zi2 = shu_zi;
    shu_zi = shu_zi1;
    shu_zi1 = shu_zi2;
    printf("shu_zi = %d,shu_zi1 = %d\n",shu_zi,shu_zi1);

    return 0;
}
