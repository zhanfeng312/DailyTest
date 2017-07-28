#include <stdio.h>

void func1();
void func2();

void (*fp)();

int main(int argc, char *argv[]){
    
	fp = func1;
	(*fp)();
	fp = func2;
	(*fp)();

	getchar();
	
	double f = 0;
	if (f == 0)
		puts("fff");

	return 0;
}

void func1(){
	printf("1\n");
}

void func2(){
	printf("2\n");
}
