/* file name	: my_stdlib.h
 * Description	: setting type and declare functions
 * */

/* DEFINE */
#define N_MAX_RECORDS 16
#define MAX_BUF 300

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

//void MY_BEST_SORT(void *, size_t, size_t, _Cmpfun *);

int my_record_keys_compare(const void *, const void *);
int my_unsigned_int_keys_compare(const void *, const void *);
void init_RECORD_array(RECORD *, int);
void init_RECORD2_array(RECORD2 *, int);
