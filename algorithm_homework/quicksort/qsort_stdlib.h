/* Description	: setting type, definition and declare function */

/* DEFINE */
#define N_MAX_RECORDS 65536
#define MAX_BUF 300
#define BRANCH 10
#define NUM_FUNC_CHECK 5
#define AVERAGE_TIME_CHECK 5

/* function type define */
typedef int _Cmpfun(const void *, const void *);


typedef struct record { 
	char hexadecimal[32]; 
	int dummy1[16];
	unsigned int key;
	char octal[32];
	int dummy2[39];
} RECORD;
typedef unsigned int RECORD2;

void QS_ITER(void *, size_t, size_t, _Cmpfun *);
void INSERT(void *, size_t, size_t, _Cmpfun *);
void QS_REC(void *, size_t, size_t, _Cmpfun *);
void QS_REC_PIVOT_INSERT(void *, size_t, size_t, _Cmpfun *);
void QS_ITER_PIVOT_INSERT(void *, size_t, size_t, _Cmpfun *);

int partition(void *, size_t, size_t, _Cmpfun*);
int my_record_keys_compare(const void *, const void *);
int my_unsigned_int_keys_compare(const void *, const void *);
void init_RECORD_array(RECORD *, int);
void init_RECORD2_array(RECORD2 *, int);

void quick_sort_change_data(RECORD *, RECORD2 *, RECORD *, RECORD2 *);
void time_check(RECORD *, RECORD2 *, RECORD *, RECORD2 *);
