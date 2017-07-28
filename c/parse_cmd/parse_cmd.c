#include <stdio.h>
#include <unistd.h>

int main (int argc, char *argv[])
{
    int opt = -1;
    while ((opt = getopt(argc, argv, "c:h")) != -1)
    {
        switch(opt) //optind初始值为1，指向下一个要处理的参数
        {
            case 'c':
                printf("argument c is %s\n", optarg);
                printf("%d\n", optind);
                break;
            case 'h':
                printf("fang\n");
                break;
        }
    }
    return 0;
}
