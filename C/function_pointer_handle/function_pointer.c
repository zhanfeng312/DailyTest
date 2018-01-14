#include <stdio.h>

void func1(void);
void func2(void);

void (*g_fp)(void) = NULL;

int main(int argc, char *argv[]){
    
	g_fp = func1;
	(*g_fp)();
    
	g_fp = func2;
	(*g_fp)();

	getchar();

	return 0;
}

void func1(void){
    
	printf("1\n");
}

void func2(void){
    
	printf("2\n");
}
