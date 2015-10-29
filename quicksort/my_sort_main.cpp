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

	init_RECORD2_array(init_array2, n);
	init_RECORD_array(init_array, n);

	
	quick_sort_change_data(array, array2, init_array, init_array2);
/*
	begin = clock();
	QS_ITER(Array2, n, sizeof(RECORD2), my_unsigned_int_keys_compare);
	end = clock();
	diff = ((double)end - (double)begin)/CLOCKS_PER_SEC;
	printf("QS_ITER time : %lf\n", diff);

	begin = clock();
	INSERT(Array2, n, sizeof(RECORD2), my_unsigned_int_keys_compare);
	end = clock();
	diff = ((double)end - (double)begin)/CLOCKS_PER_SEC;
	printf("INSERT time : %lf\n", diff);

	begin = clock();
	QS_REC(Array2, n, sizeof(RECORD2), my_unsigned_int_keys_compare);
	end = clock();
	diff = ((double)end - (double)begin)/CLOCKS_PER_SEC;
	printf("QS_REC time : %lf\n", diff);


	begin = clock();
	QS_REC_PIVOT_INSERT(Array2, n, sizeof(RECORD2), my_unsigned_int_keys_compare);
	end = clock();
	diff = ((double)end - (double)begin)/CLOCKS_PER_SEC;
	printf("QS_REC_PIVOT_INSERT time : %lf\n", diff);

	begin = clock();
	QS_ITER_PIVOT_INSERT(Array2, n, sizeof(RECORD2), my_unsigned_int_keys_compare);
	end = clock();
	diff = ((double)en*d - (double)begin)/CLOCKS_PER_SEC;
	printf("QS_ITER_PIVOT_INSERT time : %lf\n", diff);
*/
	
	

	return 0;
}
