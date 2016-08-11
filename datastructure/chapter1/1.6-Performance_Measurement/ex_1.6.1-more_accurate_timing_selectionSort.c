#include <stdio.h>
#include <time.h>
#include "selectionSort.h"
#define MAX_SIZE 1001

int main(void) 
{
	int i, n, step = 10;
	int a[MAX_SIZE];
	double duration;
	clock_t start;

	/* times for n = 0, 10, ..., 100, 200, ..., 1000 */
	printf("	n	time\n");
	for (n = 0; n <= 1000; n += step)
	{ /* get time for size n */
		/* initialize with worst-case data */
		for (i = 0; i < n; i++)
			a[i] = n - i;
		
		start = clock();
		sort(a, n);
		duration = ((double) (clock() - start)) / CLOCKS_PER_SEC;
		printf("%6d\t%f\n", n, duration);
		if (n == 100) step = 100;
	}

	return 0;
}
