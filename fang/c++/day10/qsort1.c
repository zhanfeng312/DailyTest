#include <stdio.h>
#include <string.h>
#include <stdlib.h>
static void quickSort (void* base, size_t left,
	size_t right, size_t size, int (*compar) (
	const void*, const void*)) {
	size_t p = (left + right) / 2;
	void* pivot = malloc (size);
	memcpy (pivot, base + p * size, size);
	size_t i, j;
	for (i = left, j = right; i < j;) {
		while (! (i >= p || compar (pivot,
			base + i * size) < 0))
			++i;
		if (i < p) {
			memcpy (base + p * size,
				base + i * size, size);
			p = i;
		}
		while (! (j <= p || compar (
			base + j * size, pivot) < 0))
			--j;
		if (j > p) {
			memcpy (base + p * size,
				base + j * size, size);
			p = j;
		}
	}
	memcpy (base + p * size, pivot, size);
	free (pivot);
	if (p - left > 1)
		quickSort (base, left, p - 1, size, compar);
	if (right - p > 1)
		quickSort (base, p+1, right, size, compar);
}
void my_qsort (void* base, size_t numb, size_t size,
	int (*compar) (const void*, const void*)) {
	quickSort (base, 0, numb -1, size, compar);
}
int cmpInt (const void* a, const void* b) {
	return *(const int*)a - *(const int*)b;
}
int cmpStr (const void* a, const void* b) {
	return strcmp (*(const char* const*)a,
		*(const char* const*)b);
}
int main (void) {
	int na[] = {34, 22, 19, 27, 30};
	size_t size = sizeof (na[0]);
	size_t numb = sizeof (na) / size;
//	qsort (na, numb, size, cmpInt);
	my_qsort (na, numb, size, cmpInt); //快速排序
	size_t i;
	for (i = 0; i < numb; ++i)
		printf ("%d ", na[i]);
	printf ("\n");
	const char* sa[] = {"beijing", "chongqing",
		"shanghai", "tianjin", "guangzhou"};
	size = sizeof (sa[0]);
	numb = sizeof (sa) / size;
//	qsort (sa, numb, size, cmpStr);
	my_qsort (sa, numb, size, cmpStr);
	for (i = 0; i < numb; ++i)
		printf ("%s ", sa[i]);
	printf ("\n");
	return 0;
}
