#include <stdio.h>

int main(int argc, char *argv[])
{
    /*
    行缓存：标准输入、输出
           行缓存满自动输出
           碰到换行符自动输出
           程序退出也会输出
    无缓存：标准错误不带缓存，方便及时显示出错误
    全缓存：文件IO操作，缓冲区满输出，return/exit退出时也会刷新，但通过_exit()/_Exit()退出时不会刷新
    */
    printf("hello fang");

    while (1) {
        sleep(1);
    }

    return 0;
}
