#include <stdio.h>
#include <getopt.h>

char *const short_options = "Ml:";
struct option long_options[] = {
    {"opt125_auth_60", no_argument, NULL, 'M'},
    {0, 0, 0, 0},
};

int main(int argc, char *argv[])
{
    int c, oi = 0;
    while ((c = getopt_long(argc, argv, short_options, long_options, &oi)) != -1)
    {
        switch (c)
        {
        case 'M':
            printf("This is name.\n");
            break;
        case 'l':
            printf("argument value is %s\n", optarg);
            break;
        case '?':
            break;
        }
    }

    return 0;
}