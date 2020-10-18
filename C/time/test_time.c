#include "stdio.h"
#include "time.h"
#include "stdlib.h"

int main(void){
	time_t t1, t2;
	struct tm *gmt, *area;
	
	time(&t1); //返回UTC时间 自从1970年1月1号0晨0点 到 现在的秒数
	t2 = time(NULL);

	printf("Get the seconds is %ld\n", t1);
	printf("Get the seconds is %ld\n", t2);

#if 1
	printf("Local time is: %s", ctime(&t1)); //转换为当地时间，参数为：time_t指针

	area = localtime(&t1);
	printf("Local time is: %s", asctime(area));
	printf("%d-%d-%d %2d:%2d:%.2d\n", area->tm_year + 1900, area->tm_mon + 1, 
	       area->tm_mday, area->tm_hour, area->tm_min, area->tm_sec);

	gmt = gmtime(&t1);
	printf("GMT time is: %s", asctime(gmt));

	{
		struct timeval now;

		gettimeofday(&now, NULL);
		printf("secs is %ld\n", now.tv_sec);
	}
#endif

	return 0;
}
