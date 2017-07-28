#include <stdio.h>

#pragma GCC dependency "dep.c" // 若dep.c比此文件新则产生警告
#pragma GCC poison goto float  // 若出现goto或float则产生错误

int main (void) {
//	goto escape;
//	float f;

#pragma pack(1)

	struct S1 {
		double d;
		char   c;
		int    i;
		short  h;
	}; // DDDDDDDDCIIIIHH, 15

#pragma pack()

	struct S2 {
		double d;
		char   c;
		int    i;
		short  h;
	}; // DDDDDDDDCXXXIIIIHHXX, 20

#pragma pack(8)

	struct S3 {
		double d;
		char   c;
		int    i;
		short  h;
	}; // DDDDDDDDCXXXIIIIHHXX, 20

#pragma pack()

	printf ("S1: %u字节\n", sizeof (struct S1));
	printf ("S2: %u字节\n", sizeof (struct S2));
	printf ("S3: %u字节\n", sizeof (struct S3));

	return 0;

escape:
	printf ("goto到第%d行！\n", __LINE__);
	return 0;
}
