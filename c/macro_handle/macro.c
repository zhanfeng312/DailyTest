#include <stdio.h>

#define F1(R) #R
#define F2(R) F1(R)

#define A 192.168.51.100
#define AB "http://192.168.51.100:8080"
#define CD "tomcat"


int main (void){

    if (AB != NULL)
    {
        printf("F1(A) = %s\n", F1(A)); // -> 
        printf("F2(A) = %s\n", F2(A)); // -> F1(192.168.51.100) -> "192.168.51.100"

        char buf[100] = {0};
    	snprintf(buf, sizeof (buf) - 1, AB"/sddc/dataCollect");

        printf("%s\n", buf);
    }
    else
    {
        ;
    }
	return 0;
}
