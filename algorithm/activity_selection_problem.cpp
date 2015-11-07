/* Maximum non-overlapping intervals */
/* Greedy Algorithm */
/* time complexity except sorting time : O(n) */
#include <cstdio>
#include <algorithm>

using namespace std;

typedef struct {
	int start_time;
	int finish_time;
} Activity;

int activity_cmp (const void *a, const void * b) {
	return *(Activity*)a.finish_time - *(Activity*)b.finish;
}

void greedy_iterative_activity_selector(Activity *act, int n) {
	Activity *select = new Activity [n];

	sort(act, act + n, activity_cmp);

	select = act[0];

	int i, k = 0, idx = 1;
	for (i = 1; i != n; i++) {
		if (act[i].start_time >= act[k].finish_time) {
			select[idx++] = act[i];
			k = i;
		}

	}
	
	return select;
}
