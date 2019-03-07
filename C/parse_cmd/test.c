#include <stdio.h>
#include <getopt.h>

char *const short_options = "l:m"; //定义短选项
struct option long_options[] = { //定义长选项
    {"name", no_argument, NULL, 'm'},
    {0, 0, 0, 0},
};

/*
int getopt_long(int argc, char * const argv[], const char *optstring, const struct option *longopts, int *longindex);
longindex
    longindex表示长选项在longopts中的位置
*/

int main(int argc, char *argv[])
{
    int c, oi = 0;
    while ((c = getopt_long(argc, argv, short_options, long_options, &oi)) != -1)
    {
        switch (c)
        {
        case 'm':
            printf("This is name.\n");
            break;
        case 'l':
            printf("argument value is %s\n", optarg);
            break;
        case '?':
            printf("unknown option");
            break;
        }
    }

    return 0;
}