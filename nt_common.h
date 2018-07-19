#include <stdio.h>

#define nt_log(fmt, ...) \
			do{ \
        		fprintf(stderr, "%s %d " fmt, __FUNCTION__, __LINE__,  ##__VA_ARGS__); \
    		}while(0);
