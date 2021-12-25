#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

static void GetTime1(void)
{
	time_t t1;
	time(&t1); //返回UTC时间 自从1970年1月1号0时0点 到 现在的秒数
	printf("Get the seconds from 1970 is %ld\n", t1);
	printf("Transfer the local time is: %s", ctime(&t1)); //转换为当地时间
	printf("Transfer the local time is: %s", asctime(localtime(&t1)));

	struct tm *area = localtime(&t1);
	printf("Current time is[%04d-%02d-%02d %02d:%02d:%02d]\n", area->tm_year + 1900, area->tm_mon + 1,
	        area->tm_mday, area->tm_hour, area->tm_min, area->tm_sec);
}

static void GetTime2(void)
{
	struct timeval now;
	memset(&now, 0, sizeof(now));
	gettimeofday(&now, NULL);

	printf("gettimeofday: secs:%ld, usec:%ld\n", now.tv_sec, now.tv_usec);
}

static void GetTime3(void)
{
	struct timespec now;
	memset(&now, 0, sizeof(now));
	clock_gettime(CLOCK_REALTIME, &now);

	printf("clock_gettime: secs:%ld\n", now.tv_sec);
}

int main(void)
{
	GetTime1();

	// GetTime2();

	// GetTime3();

	return 0;
}