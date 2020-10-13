#include "stdio.h"
#include "time.h"
#include "stdlib.h"

int main(void){
	time_t t;
	struct tm *gmt, *area;
	
	time(&t); //返回UTC时间 自1970 1 1到现在的秒数

	printf("Local time is: %s", ctime(&t)); //转换为当地时间，参数为：time_t指针

	area = localtime(&t);
	//printf("Local time is: %s", asctime(area));
	printf("年-月-日 时:分:秒 星期几 %d-%d-%d %2d:%2d:%.2d 星期:%d\n", area->tm_year + 1900, area->tm_mon + 1, 
	       area->tm_mday, area->tm_hour, area->tm_min, area->tm_sec, area->tm_wday);

	gmt = gmtime(&t);
	printf("GMT time   is: %s", asctime(gmt));

	struct timeval now;

	gettimeofday(&now, NULL);

	printf("secs is %ld\n", now.tv_sec);

	return 0;
}
