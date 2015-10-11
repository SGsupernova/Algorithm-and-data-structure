#include <cstdlib>
#include <cstdio>
#include "my_stdlib.h"

/* the sort that you use */
#define qsort QS_REC_PIVOT_INSERT

#define makeLine(i, n) if (!(i % n)) { printf("\n"); }

int main(void) {
	int i, n;
	RECORD Array[N_MAX_RECORDS];
	RECORD2 Array2[N_MAX_RECORDS];

	n = N_MAX_RECORDS;

	init_RECORD2_array(Array2, n);

	printf("* Data before sort: ");
	for (i = 0; i < n; i++) {
		makeLine(i, 15);
		printf(" ([%u]) ,", Array2[i]);
	}
	printf("\n\n");

	qsort(Array2, n, sizeof(RECORD2), my_unsigned_int_keys_compare);

	printf("* Data after sort: ");
	for (int i = 0; i < n; i++) {
		makeLine(i, 15);
		printf(" ([%u]) ,", Array2[i]);
	}
	printf("\n\n");

	init_RECORD_array(Array, n);

	printf("* Data before sort: ");
	for (i = 0; i < n; i++) {
		makeLine(i, 5);
		printf(" (0x%s, %d, [%u], 0%s, %d) ,", Array[i].hexadecimal, Array[i].dummy1[0], Array[i].key, Array[i].octal, Array[i].dummy2[0]);
	}
	printf("\n\n");

	qsort(Array, n, sizeof(RECORD), my_record_keys_compare);

	printf("* Data after sort: ");
	for (int i = 0; i < n; i++) {
		makeLine(i, 5);
		printf(" (0x%s, %d, [%u], 0%s, %d) ,", Array[i].hexadecimal, Array[i].dummy1[0], Array[i].key, Array[i].octal, Array[i].dummy2[0]);
	}
	printf("\n\n");

	return 0;
}
#undef qsort
#undef makeLine
