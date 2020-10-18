#include <stdio.h>

int main(int argc, char *argv[])
{
    /*
        标准输入、输出
        行缓存满自动输出
        碰到换行符自动输出
        标准错误不带缓存，方便及时显示出错误
    */
    printf("hello fang");

    while(1){

        sleep(1);
    }

    return 0;
}
