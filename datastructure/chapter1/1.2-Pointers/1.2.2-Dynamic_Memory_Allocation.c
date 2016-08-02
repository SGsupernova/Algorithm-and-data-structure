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

{
	/* Since there is the possibility that a call to malloc may fail for lack of sufficient memory,
	 * we can write a more robust version of Program. */
	if ((pi = (int*)malloc(sizeof(int))) == NULL || 
		(pf = (float*)malloc(sizeof(float))) == NULL)
	{
		fprintf(stderr, "Insufficient memory");
		exit(EXIT_FAILURE);
	}
	// or
	if (!(pi = malloc(sizeof(int))) || 
		!(pf = malloc(sizeof(float))))
	{
		fprintf(stderr, "Insufficient memory");
		exit(EXIT_FAILURE);
	}
}

/* Since malloc may be invoked from several places in your program, it is often convenient to define a macro that invokes malloc and exits when malloc fails.
 * A possible macro definition is : */
#define MALLOC(p,s) \
	if (!((p) = malloc(s))) { \
		fprintf(stderr, "Insufficient memory"); \
		exit(EXIT_FAILURE); \
	}
{
	MALLOC(pi, sizeof(int));
	MALLOC(pf, sizeof(float));
}
