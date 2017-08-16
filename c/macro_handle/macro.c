#include <stdio.h>

#define F1(R) #R
#define F2(R) F1(R)
#define A 192.168.51.100

#define UDC_SERVER "http://192.168.51.100:8080"
#define AB ff
#define CD gg

int main (void){
/*
#if defined (AB) && defined(CD)

    printf("F1(A) = %s\n", F1(A)); // -> 
    printf("F2(A) = %s\n", F2(A)); // -> F1(192.168.51.100) -> "192.168.51.100"

	char buf[] = UDC_SERVER;
	printf("%s\n", buf);
#endif
*/
    #define f(a,b) a##b
    #define g(a)  #a
    #define h(a) g(a)
    
    printf("%s\n",h(f(1,2))); // g(12)  -> 12
    printf("%s\n",g(f(1,2))); // f(1,2)
    
	return 0;
}
