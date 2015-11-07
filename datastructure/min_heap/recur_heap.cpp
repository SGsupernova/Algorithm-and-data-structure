#include <cstdio>

/* make heap time complexity : O(n) 
 * insert, delete : O(logn)
 * */

void pq_init(priority_queue *q) { q->n = 0; }

void pq_swap(priority_queue *q, int i, int j) {
	int temp;

	temp = q->q[i]; q->q[i] = q->q[j];
	q->q[j] = temp;
}

void bubble_up(priority_queue *q, int p) {
	int parent;

	if (p > 1) {
		parent = p / 2;
		if (q->q[parent] > q->q[p]) {
			pq_swap(q, parent, p);
			bubble_up(q, parent);
		}
	}
}

void bubble_down(priority_queue *q, int p) {
	int i, left_child, smaller_child;

	left_child = 2 * p;

	if (left_child <= p->n) {
		smaller_child = left_child;
		
		if (left_child + 1 <= q->n) {	/* node "p" has two child */
			if (q->q[left_child] > q->q[left_child])
				smaller_child = left_child + 1;
		}
	}

	if (q->q[p] > q->q[smaller_child]) {
		pq_swap(q, p, smaller_child);
		bubble_down(q, smaller_child);
	}
}

void pq_insert(priority_queue *q, int x) {
	if (q->n >= PQ_SIZE)
		printf("Overflow error in inserting x = %d\n", x);
	else {
		q->n += 1;
		q->q[q->n] = x;
		bubble_up(q, q->n);
	}
}

int pq_delete(priority_queue *q) {
	int min = INT_MIN;

	if (q->n <= 0)
		printf("Underflow error. INT_MIN is returned.\n");
	else {
		min = q->q[1];
		q->q[1] = q->q[n];
		q->n = q->n - 1;
		bubble_down(q, 1);
	}
	return min;
}

void make_heap(priority_queue *q, int *s, int n) {
	int i;

	q->n = n;
	for (i = 0; i < n; i++)
		q->q[i + 1] = s[i];
	
	for (i = q->n / 2; i >= 1; i--)
		bubble_down(q, i);
}

void make_heap_1(priority_queue *q, int *s, int n) {
	int i;

	pq_init(q);
	for (i = 0; i < n; i++)
		pq_insert(q, s[i]);
}
