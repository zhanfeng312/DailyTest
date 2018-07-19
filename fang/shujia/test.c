#include <stdio.h>
int main (int argc, char* argv[]){
#ifndef __cplusplus
	printf("没有定义该宏变量!\n");
#else
	printf("定义了该宏!\n");
#endif
	return 0;
}
