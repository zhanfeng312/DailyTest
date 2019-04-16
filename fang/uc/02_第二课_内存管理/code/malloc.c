#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

// 内存控制块
typedef struct mem_control_block {
	bool                      free; // 自由标志
	struct mem_control_block* prev; // 前块指针
	size_t                    size; // 本块大小
}	MCB;

MCB* g_top = NULL; // 栈顶指针

// +----------------------+              g_top
// v                      |                |
// +------+------------+--|---+------------+------+------------+
// | prev |            | prev |            | prev |            |
// | free |            | free |            | free |            |
// | size |            | size |            | size |            |
// +------+------------+------+------------+------+------------+
//   MCB  |<-- size -->|

// 分配内存
void* my_malloc (size_t size) {
	MCB* mcb;
	for (mcb = g_top; mcb; mcb = mcb->prev)
		if (mcb->free && mcb->size >= size)
			break;

	if (! mcb) {
		mcb = sbrk (sizeof (MCB) + size);
		if (mcb == (void*)-1)
			return NULL;

		mcb->prev = g_top;
		mcb->size = size;
		g_top = mcb;
	}

	mcb->free = false;

	return mcb + 1;
}

// 释放内存
void my_free (void* ptr) {
	if (! ptr)
		return;

	MCB* mcb = (MCB*)ptr - 1;
	mcb->free = true;

	for (mcb = g_top; mcb->prev; mcb = mcb->prev)
		if (! mcb->free)
			break;

	if (mcb->free) {
		g_top = mcb->prev;
		brk (mcb);
	}
	else {
		g_top = mcb;
		brk ((void*)mcb + sizeof (MCB) + mcb->size);
	}
}

int main (void) {
	int* pa[10];
	size_t size = sizeof (pa) / sizeof (pa[0]), i, j;

	for (i = 0; i < size; ++i) {
		if (! (pa[i] = (int*)my_malloc ((i + 1) * sizeof (int)))) {
			perror ("my_malloc");
			return -1;
		}

		for (j = 0; j <= i; ++j)
			pa[i][j] = j;
	}

	for (i = 0; i < size; ++i) {
		for (j = 0; j <= i; ++j)
			printf ("%d ", pa[i][j]);
		printf ("\n");
	}
	/*
	for (i = 0; i < size; ++i)
		my_free (pa[i]);
	*/
	for (;;) {
		my_free (pa[--i]);
		if (! i)
			break;
	}

	return 0;
}
