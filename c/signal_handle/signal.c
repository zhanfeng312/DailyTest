#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

/*信号处理函数*/
void handler_signal(int signum)
{
	printf("receive a signal\n");
	exit (0);
}

int main()
{
	signal(SIGINT, handler_signal);
	while(1);
	return 0;
}
