#include <stdio.h>

#define fang_log(fmt, ...) \
    do{ \
        fprintf(stderr, "[network_test] %s %d " fmt, __FUNCTION__, __LINE__,  ##__VA_ARGS__); \
    }while(0);
