#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

#define PQ_SIZE 200001

/* Goal : find minimum number of classrooms to schedule all lectures 
 * so that no two occurs at the same time in the same room */

typedef struct _lecture {
	int start_time;
	int finish_time;
} Lecture;

typedef struct {
	int classroom[PQ_SIZE + 1];
	int n; /* the number of allocated classrooms */
} priority_queue;

int lec_cmp(Lecture a, Lecture b);
void heap_adjust(priority_queue *q);
void insert_min_heap(priority_queue *q, int input);
int interval_partitioning(Lecture *lec, int n);

int main () {
	register int i;
	int n,q;
	scanf("%d", &n);

	Lecture *lec = new Lecture [n];
	for (i = 0; i < n; i++) scanf("%d %d", &lec[i].start_time, &lec[i].finish_time);

	printf("%d", interval_partitioning(lec, n));

	return 0;
}

/* n : the number of lecture */
int interval_partitioning(Lecture *lec, int n) {
	register int i, j;
	priority_queue q;

	sort(lec, lec + n, lec_cmp);

	q.n = 1;
	q.classroom[1] = lec[0].finish_time;

	for (i = 1; i != n; i++) {
		if (!(q.classroom[1] > lec[i].start_time)) {
			q.classroom[1] = lec[i].finish_time;
			heap_adjust(&q);
		}
		else {
			(q.n) ++;
			insert_min_heap(&q, lec[i].finish_time);
		}
	}
	
	return q.n;
}

int lec_cmp(Lecture a, Lecture b) {
	return a.start_time < b.start_time;
}

void heap_adjust(priority_queue *q)
/* adjust the binary tree to establish the heap */
{
	int child, n = q->n;
	int temp = q->classroom[1];
	child = 2;
	
	while (child <= n) {
		if (child < n &&
				(q->classroom[child] > q->classroom[child+1]))
			child ++;

		if (temp < q->classroom[child]) {
			/* compare root and max child */
			break;
		}
		else {
			q->classroom[child/2] = q->classroom[child]; /* move to parent */
			child *= 2;
		}
	}
	q->classroom[child/2] = temp;
}

void insert_min_heap(priority_queue *q, int input) {
	int i = q->n;
	while ((i != 1) && (input < q->classroom[i / 2])) {
		q->classroom[i] = q->classroom[i / 2];
		i /= 2;
	}
	q->classroom[i] = input;
}

