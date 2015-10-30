#include <cstdlib>
#include <cstdio>
#include <string.h>
#include "my_stdlib.h"
#include <time.h>
#include <ctime>

void QS_ITER(void * base, size_t num, size_t size, _Cmpfun * cmp) {
	size_t i, j;
	char * qi, * qj, * qp;

	while (1 < num) {
		/* initialize the variables */
		i = 0;
		j = num - 1;
		qi = (char *) base;
		qj = qi + size * j;
		qp = qj;

		/* partition about pivot */
		while (i < j) {
			while (i < j && (*cmp) (qi, qp) <= 0)
				i++, qi += size;
			while (i < j && (*cmp) (qp, qj) <= 0)
				--j, qj -= size;

			if (i < j) {
				char buf[MAX_BUF];
				char *q1 = qi;
				char *q2 = qj;
				size_t m, ms;

				/* swap as many as possible */
				for (ms = size; 0 < ms;
						ms -=m, q1 += m, q2 += m) {
					m = ms < sizeof(buf) ? ms : sizeof(buf);
					memcpy(buf, q1, m);
					memcpy(q1, q2, m);
					memcpy(q2, buf, m);
				}
			}
		}

		if (qi != qp) {
			char buf[MAX_BUF];
			char *q1 = qi;
			char *q2 = qp;
			size_t m, ms;

			for (ms = size; 0 < ms; 
					ms -= m, q1 += m, q2 += m) {
				m = ms < sizeof(buf) ? ms : sizeof(buf);
				memcpy(buf, q1, m);
				memcpy(q1, q2, m);
				memcpy(q2, buf, m);
			}
		}

		j = num - i - 1, qi += size;
		if (j < i) {
			/* recurse on smaller partition */
			if (1 < j)
				QS_ITER(qi, j, size, cmp);
			num = i;
		} else {
			/* lower partition is smaller */
			if (1 < i)
				QS_ITER(base, i, size, cmp);
			base = qi;
			num = j;
		}
	}
}

void INSERT(void * base, size_t num, size_t size, _Cmpfun* cmp) {
	int i = num - 1, j;
	char *max_loca, *begin; //max_loca : the maximum location such that the element can move
	char *temp_buf = (char*) calloc(MAX_BUF, sizeof(char));
	size_t m, ms;

	while (i-- > 0) {
		max_loca = (char *)base + size * i;

		/* save the beginning element in temp_buf */
		for (ms = size; 0 < ms; ms -= m, max_loca += m, temp_buf += m) {
			m = ms < sizeof(temp_buf) ? ms : sizeof(temp_buf);
			memcpy(temp_buf, max_loca, m);
		}
		temp_buf -= size;

		j = i;
		while (++j < num && (*cmp)(temp_buf, max_loca) > 0) {
			max_loca += size;
		}

		/* base[i] is the smallest element in the subarray from i to n - 1 */
		if (--j == i) continue;
		max_loca -= size;

		begin = (char *)base + size * i;

		/* move the each element to left */
		memcpy (begin, begin + size, size * (j - i));

		for (ms = size; 0 < ms; ms -= m, max_loca += m, temp_buf += m) {
			m = ms < sizeof(temp_buf) ? ms : sizeof(temp_buf);
			memcpy(max_loca, temp_buf, m);
		}
		temp_buf -= size;
	}

	free(temp_buf);
}


void QS_REC(void * base, size_t num, size_t size, _Cmpfun* cmp) {
	size_t i = 0, j = num - 1;
	char * qi = (char *)base,
		 * qj = qi + size * j,
		 * qp = qj;

	/* partition about pivot */
	while (i < j) {
		while (i < j && (*cmp) (qi, qp) <= 0)
			i++, qi += size;
		while (i < j && (*cmp) (qp, qj) <= 0)
			--j, qj -= size;

		if (i < j) {
			char buf[MAX_BUF];
			char *q1 = qi;
			char *q2 = qj;
			size_t m, ms;

			/* swap as many as possible */
			for (ms = size; 0 < ms;
					ms -=m, q1 += m, q2 += m) {
				m = ms < sizeof(buf) ? ms : sizeof(buf);
				memcpy(buf, q1, m);
				memcpy(q1, q2, m);
				memcpy(q2, buf, m);
			}
		}
	}

	if (qi != qp) {
		char buf[MAX_BUF];
		char *q1 = qi;
		char *q2 = qp;
		size_t m, ms;

		for (ms = size; 0 < ms; 
				ms -= m, q1 += m, q2 += m) {
			m = ms < sizeof(buf) ? ms : sizeof(buf);
			memcpy(buf, q1, m);
			memcpy(q1, q2, m);
			memcpy(q2, buf, m);
		}
	}

	j = num - i - 1, qi += size;
	if (j > 1) QS_REC(qi, j, size, cmp);
	if (i > 1) QS_REC(base, i, size, cmp);
}

void QS_REC_PIVOT_INSERT(void * base, size_t num, size_t size, _Cmpfun *cmp) {
	size_t i = 0, j = num - 1;
	char * qi = (char *)base,
		 * qj = qi + size * j,
		 * qp = qj;

	/* partition about pivot */
	while (i < j) {
		while (i < j && (*cmp) (qi, qp) <= 0)
			i++, qi += size;
		while (i < j && (*cmp) (qp, qj) <= 0)
			--j, qj -= size;

		if (i < j) {
			char buf[MAX_BUF];
			char *q1 = qi;
			char *q2 = qj;
			size_t m, ms;

			/* swap as many as possible */
			for (ms = size; 0 < ms;
					ms -=m, q1 += m, q2 += m) {
				m = ms < sizeof(buf) ? ms : sizeof(buf);
				memcpy(buf, q1, m);
				memcpy(q1, q2, m);
				memcpy(q2, buf, m);
			}
		}
	}

	if (qi != qp) {
		char buf[MAX_BUF];
		char *q1 = qi;
		char *q2 = qp;
		size_t m, ms;

		for (ms = size; 0 < ms; 
				ms -= m, q1 += m, q2 += m) {
			m = ms < sizeof(buf) ? ms : sizeof(buf);
			memcpy(buf, q1, m);
			memcpy(q1, q2, m);
			memcpy(q2, buf, m);
		}
	}


	j = num - i - 1, qi += size;

	/* If the number of elements to be sorted is less than BRANCH,
	 * we call insertion sort(INSERT) */
	if (j > 1) (j < BRANCH) ? INSERT(qi, j, size, cmp) : QS_REC_PIVOT_INSERT(qi, j, size, cmp);
	if (i > 1) (i < BRANCH) ? INSERT(base, i, size, cmp) : QS_REC_PIVOT_INSERT(base, i, size, cmp);
}



void QS_ITER_PIVOT_INSERT(void * base, size_t num, size_t size, _Cmpfun *cmp) {
	size_t i, j;
	char * qi, * qj, * qp;

	while (1 < num) {
		/* initialize the variables */
		i = 0;
		j = num - 1;
		qi = (char *) base;
		qj = qi + size * j;
		qp = qj;

		/* partition about pivot */
		while (i < j) {
			while (i < j && (*cmp) (qi, qp) <= 0)
				i++, qi += size;
			while (i < j && (*cmp) (qp, qj) <= 0)
				--j, qj -= size;

			if (i < j) {
				char buf[MAX_BUF];
				char *q1 = qi;
				char *q2 = qj;
				size_t m, ms;

				/* swap as many as possible */
				for (ms = size; 0 < ms;
						ms -=m, q1 += m, q2 += m) {
					m = ms < sizeof(buf) ? ms : sizeof(buf);
					memcpy(buf, q1, m);
					memcpy(q1, q2, m);
					memcpy(q2, buf, m);
				}
			}
		}

		if (qi != qp) {
			char buf[MAX_BUF];
			char *q1 = qi;
			char *q2 = qp;
			size_t m, ms;

			for (ms = size; 0 < ms; 
					ms -= m, q1 += m, q2 += m) {
				m = ms < sizeof(buf) ? ms : sizeof(buf);
				memcpy(buf, q1, m);
				memcpy(q1, q2, m);
				memcpy(q2, buf, m);
			}
		}

		j = num - i - 1, qi += size;
		if (j < i) {
			/* recurse on smaller partition */
			if (1 < j) (j < BRANCH) ? INSERT(qi, j, size, cmp) : QS_ITER_PIVOT_INSERT(qi, j, size, cmp);
			num = i;
		} else {
			/* lower partition is smaller */
			if (1 < i) (i < BRANCH) ? INSERT(base, i, size, cmp) : QS_ITER_PIVOT_INSERT(base, i, size, cmp);
			base = qi;
			num = j;
		}
	}
}

void MY_BEST_SORT(void * base, size_t num, size_t size, _Cmpfun *cmp) {
	size_t i = 0, j = num - 1, p;
	char * qi, * qj, * qp;

	while (1 < num) {
		/* initialize the variables */
		i = 0;
		j = num - 1;
		p = num/2;
		qi = (char *) base;
		qj = qi + size * j;
		qp = qj + p * size;

		/* partition about pivot */
		while (i < j) {
			while (i < j && (*cmp) (qi, qp) <= 0)
				i++, qi += size;
			while (i < j && (*cmp) (qp, qj) <= 0)
				--j, qj -= size;

			if (i < j) {
				char buf[MAX_BUF];
				char *q1 = qi;
				char *q2 = qj;
				size_t m, ms;

				/* swap as many as possible */
				for (ms = size; 0 < ms;
						ms -=m, q1 += m, q2 += m) {
					m = ms < sizeof(buf) ? ms : sizeof(buf);
					memcpy(buf, q1, m);
					memcpy(q1, q2, m);
					memcpy(q2, buf, m);
				}
			}
		}

		if (i > p) {--i,qi += size;}

		if (qi != qp) {
			char buf[MAX_BUF];
			char *q1 = qi;
			char *q2 = qp;
			size_t m, ms;

			for (ms = size; 0 < ms; 
					ms -= m, q1 += m, q2 += m) {
				m = ms < sizeof(buf) ? ms : sizeof(buf);
				memcpy(buf, q1, m);
				memcpy(q1, q2, m);
				memcpy(q2, buf, m);
			}
		}

		j = num - i - 1;//qi += size;
		if (j < i) {
			/* recurse on smaller partition */
			if (1 < j) (j < BRANCH) ? INSERT(qi, j, size, cmp) : QS_ITER_PIVOT_INSERT(qi, j, size, cmp);
			num = i;
		} else {
			/* lower partition is smaller */
			if (1 < i) (i < BRANCH) ? INSERT(base, i, size, cmp) : QS_ITER_PIVOT_INSERT(base, i, size, cmp);
			base = qi;
			num = j;
		}
	}
}


/* #################################################################################### */

/* #################################################################################### */



int my_record_keys_compare(const void *a, const void *b) {
	RECORD *rec_a = (RECORD *)a,
		   *rec_b = (RECORD *)b;

	return (long long int)rec_a->key - rec_b->key;
}

int my_unsigned_int_keys_compare(const void *a, const void *b) {
	RECORD2 ui_a = *(RECORD2 *)a,
			ui_b = *(RECORD2 *)b;

	return (long long int) ui_a - ui_b;
}

void init_RECORD_array(RECORD *data, int n) {
	// Generate an array with random key sequences.
	int i, j;

	for (i = 0; i < n; i++) {
		snprintf(data[i].hexadecimal, sizeof(data[i].hexadecimal), "%d", i);
		data[i].key = i;
		snprintf(data[i].octal, sizeof(data[i].octal), "%d", i);
		data[i].dummy1[0] = 2 * i;
		data[i].dummy2[0] = -i;
	}

	// Shuffle the key values using the Fisher-Yates shuffle algorithm.
	srand((unsigned int)time(NULL));

	for (i = n - 1; i >= 1; i--) {
		j = rand() % (i + 1);

		{
			// codes from qsort.c
			char buf[256];
			char *r_i = (char *)(data + i);
			char *r_j = (char *)(data + j);
			size_t m, ms;

			for (ms = sizeof(RECORD); ms > 0; ms -= m, r_i += m, r_j += m) {
				m = ms < sizeof(buf) ? ms : sizeof(buf);

				memcpy(buf, r_i, m);
				memcpy(r_i, r_j, m);
				memcpy(r_j, buf, m);
			}
		}
	}
}

void init_RECORD2_array(RECORD2 *data, int n) {
	// Generate an array with random key sequences.
	int i, j;
	RECORD2 tmp;

	for (i = 0; i < n; i++)
		data[i] = i;

	// Shuffle the key values using the Fisher-Yates shuffle algorithm.
	srand((unsigned int)time(NULL));

	for (i = n - 1; i >= 1; i--) {
		j = rand() % (i + 1);

		tmp = data[i]; data[i] = data[j]; data[j] = tmp;
	}
}


void quick_sort_change_data(RECORD * array, RECORD2 *array2, RECORD *init_array, RECORD2 * init_array2) {
	int n = N_MAX_RECORDS, chk, i;
	void (*qsort[6]) (void *, size_t, size_t, _Cmpfun*) = {QS_ITER, QS_REC, QS_REC_PIVOT_INSERT, QS_ITER_PIVOT_INSERT, MY_BEST_SORT, INSERT};
	const char * qsort_name[6] = {"QS_ITER", "QS_REC", "QS_REC_PIVOT_INSERT", "QS_ITER_PIVOT_INSERT", "MY_BEST_SORT", "INSERT"};

	init_RECORD2_array(init_array2, n);
	init_RECORD_array(init_array, n);

	chk = -1;
	/* sort ARRAY2(RECORD2) */
	while (++chk < NUM_FUNC_CHECK) {
		memcpy(array2, init_array2, sizeof(RECORD2) * n);
		printf("------- %s -------\n", qsort_name[chk]);
		printf("* Data before sort: ");
		for (i = 0; i < n; i++) {
			printf(" ([%u]) ,", array2[i]);
		}
		printf("\n\n");

		qsort[chk](array2, n, sizeof(RECORD2), my_unsigned_int_keys_compare);

		printf("* Data after sort: ");
		for (i = 0; i < n; i++) {
			printf(" ([%u]) ,", array2[i]);
		}
		printf("\n\n");
	}

	
	chk = -1;
	/* sort ARRAY(RECORD) */
	while (++chk < NUM_FUNC_CHECK) {
		memcpy(array, init_array, sizeof(RECORD) * n);
		printf("------- %s -------\n", qsort_name[chk]);
		printf("* Data before sort: ");
		for (i = 0; i < n; i++) {
			printf(" (0x%s, %d, [%u], 0%s, %d) ,", array[i].hexadecimal, array[i].dummy1[0], array[i].key, array[i].octal, array[i].dummy2[0]);
		}
		printf("\n\n");

		qsort[chk](array, n, sizeof(RECORD), my_record_keys_compare);

		printf("* Data after sort: ");
		for (i = 0; i < n; i++) {
			printf(" (0x%s, %d, [%u], 0%s, %d) ,", array[i].hexadecimal, array[i].dummy1[0], array[i].key, array[i].octal, array[i].dummy2[0]);
		}
		printf("\n\n");
	}
}

void time_check(RECORD * array, RECORD2 *array2, RECORD *init_array, RECORD2 * init_array2) {
	int i, n = N_MAX_RECORDS,j;
	clock_t begin = clock(), end = clock();
	double elapsed_secs[6] = {0, }; // double(end - begin) / CLOCKS_PER_SEC;
	void (*qsort[6]) (void *, size_t, size_t, _Cmpfun*) = {QS_ITER, QS_REC, QS_REC_PIVOT_INSERT, QS_ITER_PIVOT_INSERT, MY_BEST_SORT, INSERT};
	const char * qsort_name[6] = {"QS_ITER", "QS_REC", "QS_REC_PIVOT_INSERT", "QS_ITER_PIVOT_INSERT", "MY_BEST_SORT", "INSERT"};

	/* RECORD2 */
	i = AVERAGE_TIME_CHECK;
	while (i--) {
		init_RECORD2_array(init_array2, n);
		for (j = 0; j < NUM_FUNC_CHECK; j++) {
			memcpy(array2, init_array2, sizeof(RECORD2) * n);
			begin = clock();
			qsort[j](array2, n, sizeof(RECORD2), my_unsigned_int_keys_compare);
			end = clock();
			elapsed_secs[j] += double(end - begin) / CLOCKS_PER_SEC;
		}
	}
	printf("**** RECORD2 elapsed seconds ****\n");
	for (i = 0; i < NUM_FUNC_CHECK; i++) {
		printf("%s : %lf\n", qsort_name[i], elapsed_secs[i] / AVERAGE_TIME_CHECK);
	}


	/* RECORD */
	for (i = 0; i < NUM_FUNC_CHECK; i++) {
		elapsed_secs[i] = 0.0;
	}
	i = AVERAGE_TIME_CHECK;
	while(i--) {
		init_RECORD_array(init_array, n);
		for (j = 0; j < NUM_FUNC_CHECK; j++) {
			memcpy(array, init_array, sizeof(RECORD) * n);
			begin = clock();
			qsort[j](array, n, sizeof(RECORD), my_record_keys_compare);
			end = clock();
			elapsed_secs[j] += double(end - begin) / CLOCKS_PER_SEC;
		}
	}
	printf("**** RECORD elapsed seconds ****\n");
	for (i = 0; i < NUM_FUNC_CHECK; i++) {
		printf("%s : %lf\n", qsort_name[i], elapsed_secs[i] / AVERAGE_TIME_CHECK);
	}
}
