#include <cstdio>

#define PQ_SIZE 1000
typedef struct {
	int q[PQ_SIZE + 1];
	int n;
} priority_queue;


void pq_init(priority_queue *q);
void pq_swap(priority_queue *q, int i, int j);
void bubble_up(priority_queue *q, int p);
void bubble_down(priority_queue *q, int p);
void pq_insert(priority_queue *q, int x);
int pq_delete(priority_queue *q);
void make_heap(priority_queue *q, int *s, int n);
void make_heap_1(priority_queue *q, int *s, int n);
