/* Selection sort */

/* Suppose we must devise a program that sorts a set of n>= 1 integers. A simple solution is given by the following : 
 * From those integers that are currently unsorted, find the smallest and place it next in the sorted list */
/* written partially in c and partially in English.
	int i, n;

	for (i = 0; i < n; i++) {
		Examine list [i] to list[n - 1] and suppose that the smallest intergers is at list[min];

		Interchange list[i] and list[min];
	}
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 101
#define SWAP(x,y,t) ((t) = (x), (x) = (y), (y) = (t)) // macro version of swap
void swap (int *x, int *y);
void sort(int [], int);

int main ()
{
	int i, n;
	int list[MAX_SIZE];

	printf("Enter the number of numbers to generate : ");
	scanf("%d", &n);
	if ( n < 1 || n > MAX_SIZE) {
		fprintf(stderr, "Improper value of n\n");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < n; i++) { /* randomly generate numbers */
		list[i] = rand() % 1000;
		printf("%d ", list[i]);
	}
	sort(list, n);
	
	printf("\n Sorted array:\n");
	for (i = 0; i < n; i++) { /* print out sorted numbers */
		printf("%d\t", list[i]);
	}
	printf("\n");

	return 0;
}

void swap (int *x, int *y) 
{/* both parameters are pointers to ints */
	int temp = *x;	/* declares temp as an int and assigns to it the contents of what x points to */
	*x = *y;		/* stores what y points to into the location where x points */
	*y = temp;		/* places the contents of temp in location pointed to by y */
}

void sort(int list[], int n) // Selection sort
{
	int i, j, min, temp;
	for (i = 0; i < n - 1; i++) {
		min = i;
		for (j = i + 1; j < n; j++) {
			if (list[j] < list[min]) {
				min = j;
			}
		}
		SWAP(list[i], list[min], temp);
	}
}
