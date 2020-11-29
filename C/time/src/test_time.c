#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(void)
{
	time_t t1, t2;
	struct tm *gmt, *area;

	/*
		两种方式
	*/
	time(&t1); //返回UTC时间 自从1970年1月1号0时0点 到 现在的秒数
	printf("Get the seconds from 1970 is %ld\n", t1);
	printf("Transfer the local time is: %s", ctime(&t1)); //转换为当地时间，参数为：time_t指针

	//t2 = time(NULL);
	//printf("Get the seconds from 1970 is %ld\n", t2);

	area = localtime(&t1);
	printf("Current time is[%d-%d-%d %2d:%2d:%02d]\n", area->tm_year + 1900, area->tm_mon + 1,
	       area->tm_mday, area->tm_hour, area->tm_min, area->tm_sec);

	gmt = gmtime(&t1);
	printf("GMT time is: %s", asctime(gmt));

	{
		struct timeval now;

		gettimeofday(&now, NULL);
		printf("gettimeofday: secs:%ld, usec:%ld\n", now.tv_sec, now.tv_usec);
	}

	return 0;
}
