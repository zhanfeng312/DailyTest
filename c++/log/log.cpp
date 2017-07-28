#include <iostream>
#include <cstdio>

#define PR(fmt, ...) \
	do { \
		fprintf(stderr, "[network_macro] %s %d " fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
	}while(0)

int main(){

	PR("fang\n");
	
	return 0;
}
