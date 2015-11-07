#include <cstdio>
#include <cstring>

typedef struct {
	int key;
	/* other fields */
} element;
element list[MAX_SIZE];

#define SWAP(a, b) do { \
	unsigned char swap_temp[sizeof(x) == sizeof(y) ? -1 * printf("swap error\n")]; \
	memcpy(swap_temp, &y, sizeof(x)); \
	memcpy(&y, &x, sizeof(x)); \
	memcpy(&x, swap_temp, sizeof(x));\
} while(0)


void heapsort(element list[], int n) 
/* perform a heapsort on the array */
{
	int i, j;

	for (i = n/2; i > 0; i--)
		adjust(list, i, n);
	for(i = n-1; i > 0; i--) {
		SWAP(list[1], list[i+1]);
		adjust(list, 1, i);
	}
}

void adjust(element list[], int root, int n)
/* adjust the binary tree to establish the heap */
{
	int child, rootkey;
	element temp;
	temp = list[root];
	rootkey = list[root].key;
	child = 2 * root;		/* root child */
	
	while (child <= n) {
		if (child <= n &&
				(list[child].key < list[child + 1].key))
			child ++;

		if (rootkey > list[child].key) {
			/* compare root and max child */
			break;
		}
		else {
			list[child/2] = list[child]; /* move to parent */
			child *= 2;
		}
	
	}
	list[child/2] = temp;
}
