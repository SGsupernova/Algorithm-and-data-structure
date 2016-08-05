/* Recursive Permutation Generator */
/* Description : Given a set of n >= 1 elements, print out all possible permutations pf thos set.
 * 
 * The clue to the recursive solution is a phrase "followed by all permutations." 
 * It implies that we can solve the problem for a set with n elements if we have an algorithm that works on n - 1 elements.
 * This considerations lead to the development of this program.
 * */
#include <stdio.h>

void perm(char *list, int i, int n)
{
	/* generate all the permutations of list[i] to list[n] */
	int j, temp;
	if (i == n) {
		for (j = 0; j <= n; j++)
			printf("%c", list[j]);
		printf("\n");
	}
	else {
		/* list[i] to list[n]  has more than one permutation, generate these recursively */
		for (j = i; j <= n; j++) {
			SWAP(list[i], list[j], temp);
			perm(list, i+1, n);
			SWAP(list[i], list[j], temp);
		}
	}
}
