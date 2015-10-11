#include <cstdlib>
#include <cstdio>
#include <string.h>
#include "my_stdlib.h"
#include <time.h>

void QS_ITER(void * base, size_t num, size_t size, _Cmpfun * cmp) {
	size_t i, j;
	char * qi, * qj, * qp;

	while (1 < num) {
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
	}
	free(temp_buf);
}


void QS_REC(void * base, size_t num, size_t size, _Cmpfun cmp) {
	size_t i, j;
	char * qi, * qj, * qp;

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
	QS_ITER(qi, j, size, cmp);
	QS_ITER(base, i, size, cmp);
}

/*
   void QS_REC_PIVOT_INSERT(void * base, size_t num, size_t size, _Cmpfun cmp) {


   }

   void QS_ITER_PIVOT_INSERT(void * base, size_t num, size_t size, _Cmpfun cmp) {

   }
   */

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
