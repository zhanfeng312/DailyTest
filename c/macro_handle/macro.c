#include <stdio.h>
#include <string.h>

#define F1(R) #R
#define F2(R) F1(R)
#define A 192.168.51.100

#define AB "ddsds"
#define CD dfd

int main (void){

    if (strlen(F2(AB)) != 0 && strlen(F2(CD)) != 0)
    {
        #define UDC_USER AB
        #define UDC_PWD CD

        printf("F1(A) = %s\n", F1(A)); // -> 
        printf("F2(A) = %s\n", F2(A)); // -> F1(192.168.51.100) -> "192.168.51.100"
        
    	printf("%s:%s\n", "/data", "/data");
    }
	return 0;
}
