#include <stdio.h>
#include <stdlib.h>

int main() {
	/* 1.2.2 Dynamic Memory Allocation C provides a mechanism, called a heap, for allocating storage at run-time. 
	 * Whenever you need a new area of memory, you may call a function, malloc, and request the amount you need. 
	 * If not available. the pointer NULL is returned. 
	 *
	 * At a later time when you no longer need an area of memory, you may free it by calling another function, free, and return the are of memory to the system.
	 * Once an area of memory is freed, it is impropere to use it.
	 * On some systems the result of malloc is a char*. However, those who use ANSI C will find that the result is void*.
	 * */

	int i, *pi;
	float f, *pf;

	// The type cast expressions may be omitted.
	pi = (int *) malloc(sizeof(int));
	pf = (float *) malloc(sizeof(float));

	*pi = 1024;
	*pf = 3.14;

	printf("an integer = %d, a float = %f\n", *pi, *pf);
	free(pi);
	free(pf);

	return 0;
}
