# include <stdio.h>    //从公共目录开始查找.h文件 
int main(){

    printf("%d\n",1);  //占位
    printf("%d %d\n",1,2);
    printf("你%d 好%d吗？\n", 1, 2);
    printf("%c\n",'a');
    printf("%f %g\n", 5.7f, 5.7f);  //%g占位符在后面不会加上0
    printf("%7.3f\n",5.7);
    printf("%lf %lg\n", 5.7, 5.7);
    printf("%3d\n",1);     //3表示占用了三个位置
    printf("%03d\n",1);
    printf("%-3dabc\n",1);

    return 0;
}
