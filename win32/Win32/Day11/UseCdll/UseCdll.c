
#pragma comment(lib, "../lib/Cdll.lib")
//通知链接器 到哪 拷贝 函数的地址

int main()  //一进入main函数中,找lib文件 配套 的dll文件
{
	int sum, sub;
	sum = Cdll_add(8, 5);
	sub = Cdll_sub(8, 5);
	printf("sum = %d, sub = %d\n", sum, sub);
	return 0;
}