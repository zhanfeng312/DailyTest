#include <stdio.h>

int main(int argc, char *argv[]){
	
	char buf[512] = {0};
	
	//sscanf("123456", "%s", buf);
	//printf("%s\n", buf); 123456
	
	//sscanf("123456", "%4s", buf);
	//printf("%s\n", buf);
	
	//sscanf("123456 abcd", "%[^ ]", buf);
	//printf("%s\n", buf);
	
	sscanf("hello, world", "%*s%s", buf);
	printf("%s\n", buf);
	return 0;
}
