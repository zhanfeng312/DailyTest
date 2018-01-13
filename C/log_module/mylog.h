#ifndef LOG_H
#define LOG_H

#include <stdio.h>

#define fang_log(fmt, ...) \
	do { \
		fprintf(stderr, "[network_fang] %s %d " fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
	}while(0)

#endif //LOG_H
