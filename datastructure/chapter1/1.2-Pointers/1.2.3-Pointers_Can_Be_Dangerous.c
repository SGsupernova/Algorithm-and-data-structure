#include <stdio.h>
#include <stdlib.h>

int main () {
	int pi;
	float pf;

	pi = malloc(sizeof(int));	/* assign to pi a pointer to int */
	pf = (float *) pi; 			/* (Type Cast) casts an int pointers to a float pointer */

	// This has proven to be a dangerous practice on some computers and the programmer is urged to define explicit return types for functions.

	return 0;
}
