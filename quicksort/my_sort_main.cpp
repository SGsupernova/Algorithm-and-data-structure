#include <cstdlib>
#include <cstdio>
#include <time.h>
#include "my_stdlib.h"

int main(void) {
	int i, n;
	clock_t begin, end;
	double diff;
	RECORD array[N_MAX_RECORDS], 
		   init_array[N_MAX_RECORDS];
	RECORD2 array2[N_MAX_RECORDS], 
			init_array2[N_MAX_RECORDS];

	n = N_MAX_RECORDS;


	time_check(array, array2, init_array, init_array2);
//	quick_sort_change_data(array, array2, init_array, init_array2);

	return 0;
}
