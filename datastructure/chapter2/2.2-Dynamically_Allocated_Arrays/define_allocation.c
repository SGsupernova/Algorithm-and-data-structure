#include <stdio.h>
#include <stdlib.h>

#define MALLOC (ptr, size) \
	if (!(ptr) = malloc(size)) { \
		fprintf(stderr, "Insufficient memory"); \
		exit(EXIT_FAILURE); \
	}

#define CALLOC (ptr, num, size) \
	if (!(ptr) = calloc(num, size)) { \
		fprintf(stderr, "Insufficient memory"); \
		exit(EXIT_FAILURE); \
	}

#define REALLOC (ptr, size) \
	if (!(ptr) = realloc(ptr, size)) { \
		fprintf(stderr, "Insufficient memory"); \
		exit(EXIT_FAILURE); \
	}

